# Цель работы
Создать проект следующей функциональности:

* Плагины, оформленные в виде динамической библиотеки и выполняющие некоторую функцию библиотеки OpenCV в отдельном потоке.
* Обёртка над плагинами - класс, вызываемый основной программой, содержщий методы:
    - processAsync(Mat& img) - вызов омновной функции
    - waitForResult(Mat& img) - ожидание завершения потока
    - setParameters(const string& ymlFile) - загрузка параметров функции из YML-файла (опционально)

# Структура каталогов:   
__../bin__ - содержит основной выполняемый файл (CVwrapperTest) и библиотеки плагинов, а также картинку для теста.   
__../CW_wrapper__ - содержит класс-"обёртку" вместе с описанием базового класса для всех плагинов   
__../plugins__ - содержит каталоги с исходниками плагинов   
__../res__ - содержит YML-файлы с настройками плагинов. По умолчанию при загрузке плагина используется набор параметров из файла с таким же именем. При отсутствии файла остаются значения параметров по умолчанию (инициализация в хедере плагина).   

Каталог __./plugins__ содержит также вложенный каталог с названием _template\_plugin_. В нём находится скрипт - генератор шаблона для нового плагина.   
_Синтаксис: generate_module.sh имя_плагина_   
После генерации пустой плагин может быть сразу собран. 
Для придания нужной функциональности нужно добавить необходимые поля данных, переопределить потоковую функцию и адаптировать функцию loadParameters().
