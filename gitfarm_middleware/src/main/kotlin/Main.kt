import com.yamadalab.gitfarm.middleware.application.Git

import kotlinx.serialization.json.*

fun main() {

    val gitCurl: Git = Git();

    val commitCount: Int? = gitCurl.getCommitCount();
    println("CommitCount : $commitCount");
}