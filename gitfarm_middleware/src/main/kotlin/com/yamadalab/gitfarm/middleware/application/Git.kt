package com.yamadalab.gitfarm.middleware.application;

import kotlinx.serialization.json.Json
import kotlinx.serialization.json.int
import kotlinx.serialization.json.jsonObject
import kotlinx.serialization.json.jsonPrimitive
import java.io.File;
import java.io.FileNotFoundException;

class Git {

    companion object {
        init {
            val userHome: String = System.getProperty("user.home");
            val cppLibPath: String = "$userHome/GitFarm/gitfarm_middleware/src/main/c/build/lib";
            val cppLibName: String = System.mapLibraryName("gitfarm_middleware");
            val cppLibFullPath: String = "$cppLibPath/$cppLibName";

            try {
                val cppLibFile: File = File(cppLibFullPath);
                println("CPP Library Path : ${cppLibFile.absolutePath}");
                System.load(cppLibFile.absolutePath);
            } catch (usle: UnsatisfiedLinkError) {
                println("$usle");
            } catch (fne: FileNotFoundException) {
                println("$fne");
            }
        }
    }

    private external fun nativeGetCommits(user:String, startDate: String, endDate: String, token: String?): String;

    public fun getCommitsTotalCount(): Int? {
        val commits: String = nativeGetCommits("reidlo5135", "2024-12-07T00:00:00Z", "2024-12-07T23:59:59Z", null);

        val commitsJSON = Json.parseToJsonElement(commits).jsonObject;
        val commitsTotalCount: Int? = commitsJSON["total_count"]?.jsonPrimitive?.int;
        return commitsTotalCount;
    }
}