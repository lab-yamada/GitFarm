package com.yamadalab.gitfarm.middleware.git;

import com.yamadalab.gitfarm.middleware.utils.Utils;
import io.ktor.client.*;
import io.ktor.client.engine.cio.*;
import io.ktor.client.plugins.contentnegotiation.*;
import io.ktor.client.request.*;
import io.ktor.client.statement.*;
import io.ktor.http.*;
import io.ktor.serialization.kotlinx.json.*;
import kotlinx.serialization.json.Json;

class GitClient {

    private var token: String? = null;
    private var client: HttpClient? = null;

    init {
        this.client = HttpClient(CIO) {
            install(ContentNegotiation) {
                json()
            }
        }

        this.token = Utils.loadTokenByYaml("user_token.yaml");
    }

    private fun getClient(): HttpClient {
        return this.client!!;
    }

    suspend fun getTotalContributionsByYear(user: String, year: String): Int {
        val requestBody: Map<Any, Any> = mapOf(
            "query" to Utils.loadGraphQL("contribution_by_year.graphql")
                .replaceFirst(GRAPHQL_USER_VAL, user)
                .replace(GRAPHQL_YEAR_VAL, year)
        );

        val response: HttpResponse = this.getClient().post("https://api.github.com/graphql") {
            headers {
                append(HttpHeaders.Accept, "application/vnd.github+json");
                append(HttpHeaders.Authorization, "Bearer $token");
                append(HttpHeaders.ContentType, ContentType.Application.Json.toString());
                append("User-Agent", "GitFarm/1.0");
            }
            setBody(requestBody)
        }
        this.getClient().close();

        val gitUser: GitUser = Json.decodeFromString(response.bodyAsText());
        return gitUser.data.user.contributionsCollection.contributionCalendar.totalContributions;
    }

    companion object {
        private const val GRAPHQL_USER_VAL = "\${name}";
        private const val GRAPHQL_YEAR_VAL = "\${year}";
    }
}