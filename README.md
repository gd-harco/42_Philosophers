# <p align="center">42_Philosophers</p>

<p align="center">Final grade :<br>
<a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/cle01db6o00650fmmx6igm6z3/project/3172365" alt="gd-harco's 42 Philosophers Score" /></a>
  
## 📑 Introduction
The Philosophers project is a simulation that explores the classic synchronization problem of the dining philosophers. It aims to implement a solution to ensure the philosophers can eat without causing deadlocks or starving.

## 🍽️ Description
The philosophers simulation involves a set of philosophers sitting around a table with a bowl of rice and a chopstick placed between each pair of adjacent philosophers. The goal is to allow the philosophers to alternate between thinking and eating. However, there are some constraints:
- Each philosopher needs two chopsticks to eat.
- A chopstick can only be held by one philosopher at a time.
- Philosophers must pick up the chopsticks on their left and right to eat.
- To avoid deadlock, they must not pick up both chopsticks simultaneously.

The program should implement the solution using threads and mutexes to ensure the proper synchronization between philosophers' actions and avoid deadlocks or starvation.

## 💻 Usage
To compile the program, run the following command:
```shell
make
```
It will compile the program and create an executable called "philosophers".

To execute the simulation, use the following command:
```shell
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers`: The number of philosophers sitting at the table (at least 2).
- `time_to_die`: The time (in milliseconds) after which a philosopher dies if they haven't eaten.
- `time_to_eat`: The time (in milliseconds) it takes for a philosopher to eat.
- `time_to_sleep`: The time (in milliseconds) a philosopher spends sleeping after eating and before thinking.
- `number_of_times_each_philosopher_must_eat`: (Optional) The number of times each philosopher must eat before the simulation stops. If not provided, the simulation continues until a philosopher dies or the program is interrupted.

##  ⚠️ Warning
This project is a part of the 42-Cursus curriculum and is intended for educational purposes. If you are a current student of 42, we strongly advise you not to copy this project or submit it as your own work, as it goes against the school's academic integrity policy. We will not be responsible for any misuse of the project or academic penalties that may arise from it. However, you are welcome to use this project as a reference or for learning purposes.

## 🙇 Author
#### Your Name
- Github: [@your-github-username](https://github.com/your-github-username)<br>
<a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/cle01db6o00650fmmx6igm6z3/stats?cursusId=21&coalitionId=305" alt="gd-harco's 42 stats" /></a>
