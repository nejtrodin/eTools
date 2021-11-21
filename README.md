Набор инструментов для построения документации в соответствии с ЕСКД и совместной работы на базе Eagle CAD.

Проект крайне сырой. Замечания, предложения направлять лично автору или на svd@xakep.ru


## Реализовано

- Генерация таблицы отверстий печатной платы (учитывается только размер контактных площадок на верхнем слое). 
Штатные средства Eagle выводят только список диаметров отверстий. А производство, по старинке, требует указания диаметра контактных площадок.
- Генерация перечня элементов в соответствии с требованиями ЕСКД.
- Подготовка электрической схемы для печати в соответствии с требованиями ЕСКД (шрифты, наименования компонентов и т.д.).



## Преследуемые цели (не реализовано)

- просмотршик библиотек.
- сравнение библиотек (подсветка различий в корпусах, символах, отличия в компонентах).
- вывод информации об отличиях между библиотеками схемы и репозиторием (подключенными библиотеками).
- просмотрщик печатной платы.
- инструмент отображения компонентов на печатной плате с сортировкой по типам (номиналам), позиционным обозначениям.
- инструменты визуализации изменений в библиотеках, схемах и печатных платах
- версионный контроль проектов (с использованием Git). Файлы Eagle текстовые, поэтому удобно хранить используя систему контроля версий
- версия для Android. Разработка ведется параллельно.


## Баги

- FolderDialog на Android (проверялось на версии qt 6.0.3, Android 7.0) возвращает пустое значение выбранной папки. Пока пути приходится прописывать вручную.
