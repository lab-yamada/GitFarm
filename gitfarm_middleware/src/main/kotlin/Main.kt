import com.yamadalab.gitfarm.middleware.application.Git

import kotlinx.serialization.json.*

fun main() {

    val gitCurl: Git = Git();

    val headerArray: Array<String> = arrayOf(
        "Accept: application/vnd.github.cloak-preview",
        "User-Agent: MyApp/1.0"
    );

    val data: String = gitCurl.nativeGetCommits("reidlo5135", "2024-01-13", null);
    println("GitCurl data : $data");

    val jsonObject = Json.parseToJsonElement(data).jsonObject;

    println(jsonObject["total_count"]?.jsonPrimitive?.int);
}