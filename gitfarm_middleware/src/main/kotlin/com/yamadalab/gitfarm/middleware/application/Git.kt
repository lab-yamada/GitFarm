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
            val cppLibPath: String = "$userHome/gitfarm_ws/gitfarm_middleware/src/main/c/build/lib";
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

    public fun getCommitCount(): Int? {
        val data: String = nativeGetCommits("reidlo5135", "2024-01-01T00:00:00Z", "2024-12-31T23:59:59Z",null);
//        println("GitCurl data : $data");

        val jsonObject = Json.parseToJsonElement(data).jsonObject;
        val commitCount: Int? = jsonObject["total_count"]?.jsonPrimitive?.int;
        return commitCount;
    }
}