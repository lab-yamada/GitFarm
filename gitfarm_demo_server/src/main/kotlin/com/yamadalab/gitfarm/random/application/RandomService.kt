package com.yamadalab.gitfarm.random.application

import com.yamadalab.gitfarm.application.Random
import com.yamadalab.gitfarm.domain.Item
import lombok.RequiredArgsConstructor
import org.springframework.stereotype.Service

@Service
@RequiredArgsConstructor
class RandomService {

    public fun draw(): String {
        val random: Random = Random();

        val items: Array<Item> = arrayOf(
            Item("Item1", 0, 0.1, 0),
            Item("Item2", 0, 1.1, 1),
            Item("Item3", 0, 2.1, 2),
            Item("Item4", 0, 3.1, 3),
            Item("Item5", 0, 4.1, 4),
            Item("Item6", 0, 5.1, 5),
            Item("Item7", 0, 6.1, 6),
            Item("Item8", 0, 7.1, 7),
            Item("Item9", 0, 8.1, 8),
            Item("Item10", 0, 9.1, 9),
            Item("Item11", 0, 10.1, 10),
            Item("Item12", 0, 11.1, 11),
            Item("Item13", 0, 12.1, 12),
            Item("Item14", 0, 13.1, 13),
            Item("Item15", 0, 14.1, 14),
            Item("Item16", 0, 15.1, 15),
            Item("Item17", 0, 16.1, 16)
        );

        val drawResultId: String = random.draw(items);

        if (drawResultId == "") {
            println("DrawResultID is empty");
        } else if (drawResultId == "9999") {
            println("ItemList is Empty");
        } else if (drawResultId == "5000") {
            println("API Error");
        } else {
            println("DrawResultID : [$drawResultId]");
        }

        return drawResultId;
    }
}