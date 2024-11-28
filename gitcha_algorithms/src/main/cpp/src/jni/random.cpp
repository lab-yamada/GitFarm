#include "jni/random.h"

JNIEXPORT jstring JNICALL Java_com_yamadalab_gitcha_Random_draw(JNIEnv *jenv, jobject jobj, jobjectArray jitems)
{
    com::yamadalab::gitcha::Algorithm::SharedPtr algorithm = std::shared_ptr<com::yamadalab::gitcha::Algorithm>();

    std::vector<std::pair<std::string, std::pair<double, int>>> citems_vector;

    const jsize &jitem_size = jenv->GetArrayLength(jitems);
    printf("%s, Received jitem_size: %d\n", TAG, jitem_size);

    for (jsize i = 0; i < jitem_size; i++)
    {
        const jobject &jitem = jenv->GetObjectArrayElement(jitems, i);
        const jclass &jitem_class = jenv->GetObjectClass(jitem);

        const jfieldID &jitem_pair_first_id = jenv->GetFieldID(jitem_class, "first", "Ljava/lang/Object;");
        jstring jitem_pair_first_val = (jstring) jenv->GetObjectField(jitem, jitem_pair_first_id);

        const char *citem_id = jenv->GetStringUTFChars(jitem_pair_first_val, nullptr);
        printf("%s, citem_id : %s\n", TAG, citem_id);

        const jfieldID &jpair_second_id = jenv->GetFieldID(jitem_class, "second", "Ljava/lang/Object;");
        const jobject &jpair_second_val = jenv->GetObjectField(jitem, jpair_second_id);

        const jclass &jitem_info_pair_class = jenv->GetObjectClass(jpair_second_val);
        const jfieldID &jitem_info_pair_first_id = jenv->GetFieldID(jitem_info_pair_class, "first", "D");
        const jdouble &jprobability = jenv->GetDoubleField(jpair_second_val, jitem_info_pair_first_id);
        const double &cprobability = static_cast<double>(jprobability);

        const jfieldID &jitem_info_pair_second_id = jenv->GetFieldID(jitem_info_pair_class, "second", "I");
        const jint &jfail_count = jenv->GetIntField(jpair_second_val, jitem_info_pair_second_id);
        const int &cfail_count = static_cast<int>(jfail_count);

        citems_vector.push_back({std::string(citem_id), {cprobability, cfail_count}});

        jenv->ReleaseStringUTFChars(jitem_pair_first_val, citem_id);
    }

    std::string draw_result_id = algorithm->draw(citems_vector);
    jenv->NewStringUTF(draw_result_id.c_str());

    return jenv->NewStringUTF(draw_result_id.c_str());
}