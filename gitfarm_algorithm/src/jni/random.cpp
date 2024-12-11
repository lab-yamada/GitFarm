#include "jni/random.h"

com::yamadalab::gitfarm::Algorithm::SharedPtr algorithm_ = std::make_shared<com::yamadalab::gitfarm::Algorithm>();

JNIEXPORT jboolean JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_application_Random_nativeSetItems(JNIEnv *jEnv, jobject jObj, jobjectArray jItems)
{
    std::vector<com::yamadalab::gitfarm::Item> cItems;

    const jsize &jItemSize = jEnv->GetArrayLength(jItems);

    for (jsize i=0;i<jItemSize;i++)
    {
        com::yamadalab::gitfarm::Item::SharedPtr cItem = std::make_shared<com::yamadalab::gitfarm::Item>();

        const jobject &jItem = jEnv->GetObjectArrayElement(jItems, i);
        const jclass &jItemClass = jEnv->GetObjectClass(jItem);

        const jfieldID &jItemIdField = jEnv->GetFieldID(jItemClass, "first", JNI_OBJECT);
        const jstring &jItemId = static_cast<jstring>(jEnv->GetObjectField(jItem, jItemIdField));
        const char *cItemId = jEnv->GetStringUTFChars(jItemId, nullptr);

        const jfieldID &jItemGradeField = jEnv->GetFieldID(jItemClass, "second", JNI_OBJECT);
        const jstring &jItemGrade = static_cast<jstring>(jEnv->GetObjectField(jItem, jItemGradeField));
        const char *cItemGrade = jEnv->GetStringUTFChars(jItemGrade, nullptr);

        cItem->set__id(std::string(cItemId));
        cItem->set__grade(std::string(cItemGrade));
        cItems.push_back(*cItem);

        jEnv->ReleaseStringUTFChars(jItemId, cItemId);
        jEnv->ReleaseStringUTFChars(jItemGrade, cItemGrade);
    }

    algorithm_->set__items(cItems);

    bool isItemUpdated = (algorithm_->get__items().size() > 0);
    if (isItemUpdated)
    {
        fprintf(stdout, "%s, Item updated with size : %lu\n", LOG_JNI, algorithm_->get__items().size());
    }
    else
    {
        fprintf(stdout, "%s, Item update Failed", LOG_JNI);
    }

    return isItemUpdated;
}

JNIEXPORT jboolean JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_application_Random_nativeSetUser(JNIEnv *jEnv, jobject jObj, jobject jUser)
{
    jclass jUserClass = jEnv->GetObjectClass(jUser);

    if (jUserClass == nullptr)
    {
        fprintf(stderr, "%s, Error getting user class\n", LOG_JNI);
    }

    jfieldID jUserNameField = jEnv->GetFieldID(jUserClass, "name", JNI_STRING);

    if (jUserNameField == nullptr)
    {
        fprintf(stderr, "%s, Error getting user name field\n", LOG_JNI);
    }

    jfieldID jUserFailCountField = jEnv->GetFieldID(jUserClass, "failCount", JNI_INT);

    if (jUserFailCountField == nullptr)
    {
        fprintf(stderr, "%s, Error getting user failCount field\n", LOG_JNI);
    }

    jstring jUserName = static_cast<jstring>(jEnv->GetObjectField(jUser, jUserNameField));
    const char *cUserName = jEnv->GetStringUTFChars(jUserName, nullptr);

    if (cUserName == nullptr || cUserName == "")
    {
        fprintf(stderr, "%s, Error getting user name\n", LOG_JNI);
        return JNI_FALSE;
    }

    jint jUserFailCount = jEnv->GetIntField(jUser, jUserFailCountField);

    com::yamadalab::gitfarm::User::SharedPtr user = std::make_shared<com::yamadalab::gitfarm::User>();
    user->set__id(cUserName);
    user->set__fail_count(jUserFailCount);

    algorithm_->set__user(user);
    fprintf(stdout, "%s, User Set succeeded with name : %s, failCount : %d \n", LOG_JNI, cUserName, jUserFailCount);

    return JNI_TRUE;
}

JNIEXPORT jobject JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_application_Random_nativeDraw(JNIEnv *jEnv, jobject jObj)
{
    const std::vector<com::yamadalab::gitfarm::Item> &cItems = algorithm_->get__items();
    if (cItems.empty() || cItems.size() <= 0)
    {
        printf("%s, WrsDraw, cItems is empty", LOG_JNI);
        return nullptr;
    }

    const com::yamadalab::gitfarm::Item::SharedPtr &cDrawItem = algorithm_->draw();

    const jclass &jItemClass = jEnv->FindClass(JITEM_PATH);

    if (jItemClass == nullptr)
    {
        printf("%s jItemClass is null", LOG_JNI);
        return nullptr;
    }

    const jclass &jItemGradeClass = jEnv->FindClass(JITEM_GRADE_PATH);

    if (jItemGradeClass == nullptr)
    {
        printf("%s jItemGradeClass is null", LOG_JNI);
        return nullptr;
    }

    const jmethodID &jItemConstructor = jEnv->GetMethodID(jItemClass, "<init>", JITEM_CONSTRUCTOR);
    if (jItemConstructor == nullptr)
    {
        printf("%s jItemConstructor is null", LOG_JNI);
        return nullptr;
    }

    const jstring &jItemId = jEnv->NewStringUTF(cDrawItem->get__id().c_str());
    const jstring &jItemGrade = jEnv->NewStringUTF(cDrawItem->get__grade().c_str());

    const jobject &jItem = jEnv->NewObject(jItemClass, jItemConstructor, jItemId, jItemGrade);

    jEnv->DeleteLocalRef(jItemId);
    jEnv->DeleteLocalRef(jItemGrade);

    return jItem;
}