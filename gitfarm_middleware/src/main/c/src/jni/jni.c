#include "jni/jni.h"

jint JNI_parse_to_jint(JNIEnv *jenv, jobject jobj)
{
    jclass jint_class = (*jenv)->FindClass(jenv, "java/lang/Integer");
    jmethodID int_value_method = (*jenv)->GetMethodID(jenv, jint_class, "intValue", "()I");
    return (*jenv)->CallIntMethod(jenv, jobj, int_value_method);
}

jstring JNI_parse_to_jstring(JNIEnv *jenv, jobject jobj)
{
    return (jstring)jobj;
}

jdouble JNI_parse_to_jdouble(JNIEnv *jenv, jobject jobj)
{
    jclass jdouble_class = (*jenv)->FindClass(jenv, "java/lang/Double");
    jmethodID double_value_method = (*jenv)->GetMethodID(jenv, jdouble_class, "doubleValue", "()D");
    return (*jenv)->CallDoubleMethod(jenv, jobj, double_value_method);
}

jfloat JNI_parse_to_jfloat(JNIEnv *jenv, jobject jobj)
{
    jclass jfloat_class = (*jenv)->FindClass(jenv, "java/lang/Float");
    jmethodID float_value_method = (*jenv)->GetMethodID(jenv, jfloat_class, "floatValue", "()F");
    return (*jenv)->CallFloatMethod(jenv, jobj, float_value_method);
}