![eng](img/eng.png) [![ru](img/ru.png)](README.ru.md)
# `Philosophers`

Project in Ecole42. The purpose of this project is to learn how to work with `threads`, `mutex`, `semaphores`.<br>
You can read task: [`philosophers.subject.pdf`](subject/philosophers.subject.pdf)

### Discription
It is classic task about [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).
For do this task, you need know some rules:
- One or more philosophers sit at a round table
- The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because eating with only one fork is very inconvenient, a
philosopher takes two forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying.

Programm take 4 or 5 arguments and looks like:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
```
- __number_of_philosophers__: The number of philosophers and also the number of forks.
- __time_to_die__ (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- __time_to_eat__ (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- __time_to_sleep__ (in milliseconds): The time a philosopher will spend sleeping.
- __number_of_times_each_philosopher_must_eat__ (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

In program runtime any state change of a philosopher must be formatted as follows:
```bash
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
__timestamp_in_ms__ and __X__ replace by:
- __timestamp_in_ms__ - the current timestamp in milliseconds
- __X__ - philosopher number (from 1 to number_of_philosopher)

#### Specific rules
__Mandatory path__:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

__Bonus part__:
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process. But the main process should not be a philosopher.

### Evaluated by moulinette

![125/100](img/125.png)
