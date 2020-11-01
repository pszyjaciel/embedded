
 /* This is a one-cycle loop that simplifies error handling */
 //do
 //{
	 //...modestly complex code, including a nested loop...
 //} while (0);

/* file: minunit.h */
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)

int tests_run;
int runUnitTest();