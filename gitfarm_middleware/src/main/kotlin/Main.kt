
import com.yamadalab.gitfarm.middleware.algorithm.application.Random
import com.yamadalab.gitfarm.middleware.algorithm.domain.Grade
import com.yamadalab.gitfarm.middleware.algorithm.domain.Item
import com.yamadalab.gitfarm.middleware.algorithm.domain.User
import com.yamadalab.gitfarm.middleware.git.application.GitClient
import kotlinx.coroutines.runBlocking

fun main() {
    val random: Random = Random();

    val items: Array<Item> = arrayOf(
        Item("Item1", Grade.S),
        Item("Item2", Grade.S),
        Item("Item3", Grade.A),
        Item("Item4", Grade.A),
        Item("Item5", Grade.A),
        Item("Item6", Grade.B),
        Item("Item7", Grade.B),
        Item("Item8", Grade.B),
        Item("Item9", Grade.B),
        Item("Item10", Grade.C),
        Item("Item11", Grade.C),
        Item("Item12", Grade.C),
        Item("Item13", Grade.C),
        Item("Item14", Grade.D),
        Item("Item15", Grade.D),
        Item("Item16", Grade.D),
        Item("Item17", Grade.D)
    );

    val isItemUpdated: Boolean = random.updateItems(items = items);

    if (isItemUpdated) {
        println("Item Updated");
    } else {
        println("Item Update Failed");
    }

    val user: User = User("reidlo5135", 100);
    val isUserUpdated: Boolean = random.setUser(user = user);

    if (isUserUpdated) {
        println("User Set Succeeded");
    } else {
        println("User Set Failed");
    }

    val gitClient: GitClient = GitClient();
    runBlocking {
        val totalContributions: Int = gitClient.getTotalContributionsByYear("reidlo5135", "2024");
        println("totalContributions : $totalContributions");

        for (i: Int in 1 .. totalContributions / 10) {
            val drawItem: Item = random.draw();
            println("DrawItem : [$drawItem][$i]");

            if (drawItem.grade.toString() == Grade.S.toString()) {
                user.failCount = 0;
                random.setUser(user);
                println("S Selected By User : $user");
            } else {
                user.failCount++;
                random.setUser(user);
            }
        }
    }
}