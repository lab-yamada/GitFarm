import com.yamadalab.gitfarm.middleware.application.Git

fun main() {

    val git: Git = Git();

    val commitsTotalCount: Int? = git.getCommitsTotalCount();
    println("CommitCount : $commitsTotalCount");
}