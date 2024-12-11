#include "algorithm/algorithm.hpp"

/**
 *	@class com::yamadalab::gitfarm::Algorithm
 *	@author reidlo
 *	@date 2024.12.11
 ***/
namespace com::yamadalab::gitfarm
{
	Algorithm::Algorithm() = default;
	Algorithm::~Algorithm() = default;

	std::vector<Item> Algorithm::get__items() const
	{
		return this->items_;
	}

	void Algorithm::set__items(const std::vector<Item> &items)
	{
		this->items_ = items;
	}

	User::SharedPtr Algorithm::get__user() const
	{
		return this->user_;
	}

	void Algorithm::set__user(const User::SharedPtr &user)
	{
		this->user_ = user;
	}

	bool Algorithm::is_ready_to_draw()
	{
		bool is_items_set = false;

		if (this->get__items().empty() || this->get__items().size() <= 0)
		{
			fprintf(stderr, "IsReadyToDraw, items is empty\n");
			is_items_set = false;
		}
		else if (this->get__user() == nullptr)
		{
			fprintf(stderr, "IsReadyToDraw, user is nullptr\n");
			is_items_set = false;
		}
		else
		{
			is_items_set = true;
		}

		return is_items_set;
	}


	void Algorithm::weight_items_by_grade()
	{
		const bool &is_ready_to_draw = this->is_ready_to_draw();
		if (!is_ready_to_draw)
		{
			fprintf(stderr, "WeightItemsByGrade, items is empty\n");
			return;
		}

		const std::vector<Item> &origin_items = this->get__items();
		std::vector<Item> weighted_items;

		const double &default_weight = 100 / origin_items.size();

		for (const Item &origin_item : origin_items)
		{
			Item::UniquePtr weighted_item = std::make_unique<Item>(origin_item);
			const std::string &origin_grade = origin_item.get__grade();

			double weight = default_weight;

			if (origin_grade == GRADE_S)
			{
				weight *= WEIGHT_S;
			}
			else if (origin_grade == GRADE_A)
			{
				weight *= WEIGHT_A;
			}
			else if (origin_grade == GRADE_B)
			{
				weight *= WEIGHT_B;
			}
			else if (origin_grade == GRADE_C)
			{
				weight *= WEIGHT_C;
			}
			else if (origin_grade == GRADE_D)
			{
				weight *= WEIGHT_D;
			}
			else
			{
				fprintf(stderr, "WeightItemsByGrade, Unknown Grade\n");
			}

			weighted_item->set__weight(weight);
			weighted_items.push_back(std::move(*weighted_item));
		}
		this->set__items(weighted_items);
	}

	void Algorithm::weight_items_by_pity()
	{
		const bool &is_ready_to_draw = this->is_ready_to_draw();
		if (!is_ready_to_draw)
		{
			fprintf(stderr, "WeightItemsByGrade, items or user is empty\n");
			return;
		}

		const std::vector<Item>& origin_items = this->get__items();
		std::vector<Item> weighted_items;

		for (const Item &origin_item : origin_items)
		{
			const User::SharedPtr &user = this->get__user();
			const int &user_fail_count = user->get__fail_count();

			Item::UniquePtr weighted_item = std::make_unique<Item>(origin_item);

			const double &origin_weight = origin_item.get__weight();

			if (user_fail_count == PITY_MAX_WEIGHT)
			{
				// fprintf(stdout, "!!! MAX PITY !!!\n");
				weighted_item->set__weight(PITY_MAX_WEIGHT * PITY_MAX_WEIGHT);
				weighted_items.push_back(std::move(*weighted_item));
				user->set__fail_count(0);
				continue;
			}

			const bool &is_pity = this->pity_select(origin_weight, user_fail_count);

			if (is_pity)
			{
				weighted_item->set__weight(origin_weight + PITY_WEIGHT);
			}
			else
			{
				weighted_item->set__weight(origin_weight);
			}
			weighted_items.push_back(std::move(*weighted_item));
		}
		this->set__items(weighted_items);
	}

	Item::SharedPtr Algorithm::weight_random_select()
	{
		const bool &is_ready_to_draw = this->is_ready_to_draw();
		if (!is_ready_to_draw)
		{
			fprintf(stderr, "WeightItemsByGrade, items is empty\n");
			return nullptr;
		}

		const std::vector<Item>& items = this->get__items();

		double total_weight = 0.0;

		for (const Item& item : items)
		{
			total_weight += item.get__weight();
		}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(0, total_weight - 1);
		const int &random_val = dist(gen);

		double current_weight = 0.0;
		for (const Item& item : items)
		{
			current_weight += item.get__weight();

			if (random_val < current_weight)
			{
				const Item::SharedPtr &result_item = std::make_shared<Item>(item);
				return result_item;
			}
		}

		throw std::runtime_error("wrs_random: No item selected, check weights and input data");
	}

	bool Algorithm::pity_select(const int &weight, const int &fail_count)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		int current_chance = weight + (fail_count * 10);
		current_chance = std::min(current_chance, 100);

		std::uniform_int_distribution<> dist(1, 100);
		const int &roll = dist(gen);
		const bool &is_pity = (roll <= current_chance);

		return is_pity;
	}

	Item::SharedPtr Algorithm::draw()
	{
		this->weight_items_by_grade();
		this->weight_items_by_pity();

		const Item::SharedPtr &draw_item = this->weight_random_select();

		return draw_item;
	}

}