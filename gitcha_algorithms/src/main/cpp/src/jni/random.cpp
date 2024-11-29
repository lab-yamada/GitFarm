#include "jni/random.h"

JNIEXPORT jstring JNICALL Java_com_yamadalab_gitcha_application_Random_cdraw(JNIEnv *jenv, jobject jobj, jobjectArray jitems)
{
    std::string draw_result_id = "";
    com::yamadalab::gitcha::Algorithm::SharedPtr algorithm = std::shared_ptr<com::yamadalab::gitcha::Algorithm>();

    std::vector<std::pair<std::string, std::pair<double, int>>> citems_vector;

    const jsize &jitem_size = jenv->GetArrayLength(jitems);
    printf("%s, Received jitem_size: %d\n", TAG, jitem_size);

    for (jsize i = 0; i < jitem_size; i++)
    {
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

        citems_vector.push_back({std::string(citem_id), {cprobability, cfail_count}});

        jenv->ReleaseStringUTFChars(jitem_id, citem_id);
    }

    for (const auto &citem : citems_vector)
    {
        printf("%s, citem\n\tid : %s\n\tprobability : %f\n\tfail_count : %d\n", TAG, citem.first.c_str(), citem.second.first, citem.second.second);
    }

    draw_result_id = algorithm->draw(citems_vector);
    printf("%s, draw_result_id : %s", TAG, draw_result_id.c_str());
    jenv->NewStringUTF(draw_result_id.c_str());

    return jenv->NewStringUTF(draw_result_id.c_str());
}