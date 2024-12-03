import com.yamadalab.gitfarm.middleware.application.GitCurl

import kotlinx.serialization.json.*

fun main() {

    val gitCurl: GitCurl = GitCurl();

    val data: String = gitCurl.nativePostRequest("http://localhost:8080/curl");
    println("GitCurl data : $data");

    val jsonObject = Json.parseToJsonElement(data).jsonObject;

    println(jsonObject["key1"]?.jsonPrimitive?.content);
    println(jsonObject["key2"]?.jsonPrimitive?.int);
    println(jsonObject["nested"]?.jsonObject?.get("nestedKey")?.jsonPrimitive?.content);
}