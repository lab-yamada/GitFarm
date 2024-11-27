#include "jni/random.h"

JNIEXPORT jint JNICALL Java_com_yamadalab_gitcha_Random_wrsRandom(
    JNIEnv *jenv, jobject jobj,
    jlongArray jweights)
{
    jsize jweights_len = jenv->GetArrayLength(jweights);
    jlong* jweight_elements = jenv->GetLongArrayElements(jweights, nullptr);

    std::vector<int> cweights;
    cweights.reserve(jweights_len);

    for (jsize i = 0; i < jweights_len; i++)
    {
        cweights.push_back(static_cast<int>(jweight_elements[i]));
    }
    jenv->ReleaseLongArrayElements(jweights, jweight_elements, JNI_ABORT);

    int cresult = com::yamadalab::gitcha::wrs_random(cweights);

    return static_cast<jint>(cresult);
}

JNIEXPORT jboolean JNICALL Java_com_yamadalab_gitcha_Random_pityRandom(
    JNIEnv *jenv, jobject jobj,
    jint jbase_chance, jint jmax_fails, jint jcurrent_fails)
{
    const int &cbase_chance = static_cast<int>(jbase_chance);
    const int &cmax_fails = static_cast<int>(jmax_fails);
    const int &ccurrent_fails = static_cast<int>(jcurrent_fails);

    const bool &cresult = com::yamadalab::gitcha::pity_random(cbase_chance, cmax_fails, ccurrent_fails);

    return static_cast<jboolean>(cresult);
}