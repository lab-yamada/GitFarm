package com.yamadalab.gitfarm.middleware.gclient;

import com.yamadalab.gitfarm.middleware.utils.Utils
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.int
import kotlinx.serialization.json.jsonObject
import kotlinx.serialization.json.jsonPrimitive
import java.io.FileNotFoundException;

class Git {

    companion object {
        init {
            try {
                Utils.loadSharedLibrary("gitfarm_gclient");
            } catch (usle: UnsatisfiedLinkError) {
                println("$usle");
            } catch (fne: FileNotFoundException) {
                println("$fne");
            }
        }
    }

    private external fun nativeGetCommits(user:String, startDate: String, endDate: String, token: String?): String;

    public fun getCommitsTotalCount(): Int? {
        val commits: String = nativeGetCommits("jin-daram", "2024-01-01T00:00:00Z", "2024-12-31T23:59:59Z",null);

        val commitsJSON = Json.parseToJsonElement(commits).jsonObject;
        val commitsTotalCount: Int? = commitsJSON["total_count"]?.jsonPrimitive?.int;
        return commitsTotalCount;
    }
}