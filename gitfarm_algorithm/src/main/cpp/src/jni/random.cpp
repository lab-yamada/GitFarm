#include "jni/random.h"

com::yamadalab::gitfarm::Algorithm::SharedPtr algorithm_ = std::make_shared<com::yamadalab::gitfarm::Algorithm>();

JNIEXPORT void JNICALL
Java_com_yamadalab_gitfarm_algorithm_application_Random_nativeSetItems(JNIEnv *jenv, jobject jobj, jobjectArray jitems)
{
    std::vector<com::yamadalab::gitfarm::Item> citems;

    const jsize &jitem_size = jenv->GetArrayLength(jitems);

    for (jsize i=0;i<jitem_size;i++)
    {
        com::yamadalab::gitfarm::Item::SharedPtr citem = std::make_shared<com::yamadalab::gitfarm::Item>();

        const jobject &jitem = jenv->GetObjectArrayElement(jitems, i);
        const jclass &jitem_class = jenv->GetObjectClass(jitem);

        const jfieldID &jitem_id_field = jenv->GetFieldID(jitem_class, "first", "Ljava/lang/Object;");
        const jstring &jitem_id = (jstring) jenv->GetObjectField(jitem, jitem_id_field);
        const char *citem_id = jenv->GetStringUTFChars(jitem_id, nullptr);

        const jfieldID &jpair_second_id = jenv->GetFieldID(jitem_class, "second", "Ljava/lang/Object;");
        const jobject &jpair_second_val = jenv->GetObjectField(jitem, jpair_second_id);

        const jclass &jitem_info_pair_class = jenv->GetObjectClass(jpair_second_val);

        const jfieldID &jprobability_field = jenv->GetFieldID(jitem_info_pair_class, "first", "Ljava/lang/Object;");
        const jobject &jprobability_object = jenv->GetObjectField(jpair_second_val, jprobability_field);
        const jdouble &jprobability = JNI_parse_to_jdouble(jenv, jprobability_object);
        const double &cprobability = static_cast<double>(jprobability);

        const jfieldID &jfail_count_field = jenv->GetFieldID(jitem_info_pair_class, "second", "Ljava/lang/Object;");
        const jobject &jfail_count_object = jenv->GetObjectField(jpair_second_val, jfail_count_field);
        const jint &jfail_count = JNI_parse_to_jint(jenv, jfail_count_object);
        const int &cfail_count = static_cast<int>(jfail_count);

        citem->set__id(std::string(citem_id));
        citem->set__probability(cprobability);
        citem->set__fail_count(cfail_count);

        citems.push_back(*citem);

        jenv->ReleaseStringUTFChars(jitem_id, citem_id);
    }

    algorithm_->set__items(citems);
}

JNIEXPORT jobject JNICALL
Java_com_yamadalab_gitfarm_algorithm_application_Random_nativeDraw(JNIEnv *jenv, jobject jobj)
{
    const std::vector<com::yamadalab::gitfarm::Item> &citems = algorithm_->get__items();
    if (citems.empty())
    {
        printf("%s, WrsDraw, citems is empty");
        return nullptr;
    }
    
    std::vector<com::yamadalab::gitfarm::Item> cweighted_items;
    for (const com::yamadalab::gitfarm::Item &citem : citems)
    {
        com::yamadalab::gitfarm::Item::SharedPtr cweighted_item = std::make_shared<com::yamadalab::gitfarm::Item>();

        int cweight = 0;
        const double &cprobability = citem.get__probability();
        const double &cfail_count = citem.get__fail_count();

        const bool &is_pity = algorithm_->pity_draw(cprobability, cfail_count);

        if (is_pity == true)
        {
            cweight = PITY_WEIGHT;
        }
        else
        {
            cweight = 0;
        }

        cweighted_item->set__id(citem.get__id());
        cweighted_item->set__weight(cweight);
        cweighted_item->set__probability(cprobability);
        cweighted_item->set__fail_count(cfail_count);
        cweighted_items.push_back(*cweighted_item);
    }

    const com::yamadalab::gitfarm::Item &cdraw_item = algorithm_->wrs_draw(cweighted_items);

    const jclass &jitem_class = jenv->FindClass("com/yamadalab/gitfarm/algorithm/domain/Item");

    if (jitem_class == nullptr)
    {
        printf("%s jItemClass is null", TAG);
        return nullptr;
    }

    jmethodID jitem_constructor = jenv->GetMethodID(jitem_class, "<init>", "(Ljava/lang/String;IDI)V");
    if (jitem_constructor == nullptr)
    {
        printf("%s jItemConstructor is null", TAG);
        return nullptr;
    }

    jstring jid = jenv->NewStringUTF(cdraw_item.get__id().c_str());
    jint jweight = cdraw_item.get__weight();
    jdouble jprobability = cdraw_item.get__probability();
    jint jfail_count = cdraw_item.get__fail_count();

    jobject jitem = jenv->NewObject(jitem_class, jitem_constructor, jid, jweight, jprobability, jfail_count);

    jenv->DeleteLocalRef(jid);

    return jitem;
}