/* 
 * queue-objects.h -- public interface for making objects that can be added to a queue
 */

#define MAXNAM 50
#define MAXREG 10

typedef struct personq {
	char name[MAXREG];
	int age;
	double height;
} personq_t;

typedef struct carq {
	char plate[MAXREG];
	double price;
	int year;
} carq_t;

personq_t *make_person(char* name, int age, double height);

carq_t *make_car(char* plate, double price, int year);





