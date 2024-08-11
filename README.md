## What this is
This is a task from one of the my interviews. Basically, it's just an external sort.

### Task text (translate)
A tape-type data storage device is designed for sequential recording and reading of data. The read/write magnetic head is stationary during reading and writing, and the tape can move in both directions. Writing and reading information is possible in the tape cell on which the magnetic head is currently located. Moving the tape is a time-consuming operation - the tape is not designed for random access.

There is an input tape of length N (where N is large) containing elements of type integer (2<sup>32</sup>). There is an output tape of the same length. It is necessary to write elements from the input tape, sorted in ascending order, into the output tape. There is a limitation on the use of RAM - no more than M bytes (M can be < N, i.e. it will not be possible to load all the data from the tape into RAM). To implement the algorithm, you can use a reasonable number of time tapes, i.e. tapes on which you can store some temporary information necessary during the operation of the algorithm.

You need to create a C++ project that compiles into a console application that implements an algorithm for sorting data from the input tape to the output tape. You need to do the following:
- Define an interface for working with a tape type device.
- Write a class that implements this interface and emulates working with the tape using a regular file. It should be possible to configure (without recompilation - for example, through an external configuration file that will be read at the start of the application) delays for writing/reading an element from the tape, rewinding the tape, and shifting the tape by one position.
- Temporary tape files can be saved to the tmp directory.
- Write a class that implements an algorithm for sorting data from the input tape to the output tape.
- The console application must accept the name of the input and output files as input and perform sorting.
- It is advisable to write unit tests.

### Original task text
Устройство хранения данных типа лента (Tape) предназначено для последовательной записи и чтения данных. Считывающая/записывающая магнитная головка неподвижна во время чтения и записи, а лента имеет возможность двигаться в обоих направлениях. Запись и чтение информации возможны в ячейку ленты, на которой в данный момент находится магнитная головка. Перемещения ленты – затратная по времени операция – лента не предназначена для произвольного доступа.

Имеется входная лента длины N (где N – велико), содержащая элементы типа integer (2<sup>32</sup>). Имеется выходная лента такой же длины. Необходимо записать в выходную ленту отсортированные по возрастанию элементы с входной ленты. Есть ограничение по использованию оперативной памяти – не более M байт (M может быть < N, т.е. загрузить все данные с ленты в оперативную память не получится). Для реализации алгоритма можно использовать разумное количество временных лент, т.е. лент, на которых можно хранить какую-то временную информацию, необходимую в процессе работы алгоритма.

Необходимо создать проект С++, компилируемый в консольное приложение, которое реализует алгоритм сортировки данных с входной ленты на выходную. Необходимо сделать следующее:
- Определить интерфейс для работы с устройством типа лента.
- Написать класс, реализующий этот интерфейс и эмулирующий работу с лентой посредством обычного файла. Должно быть возможно сконфигурировать (без перекомпиляции – например, через внешний конфигурационный файл, который будет прочитан на старте приложения) задержки по записи/чтению элемента с ленты, перемотки ленты, и сдвига ленты на одну позицию.
- Файлы временных лент можно сохранять в директорию tmp.
- Написать класс, реализующий алгоритм сортировки данных с входной ленты на выходную.
- Консольное приложение должно принимать на вход имя входного и выходного файлов и производить сортировку.
- Желательно написать юнит-тесты.
