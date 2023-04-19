Добавили изменения для ветки reset
Добавили изменения для ветки reset
Добавили изменения для ветки reset
Добавили изменения для ветки reset
еще одна правка 
## Про Git

Существует несколько систем контроля версий: Git, Subversion, Team Foundation Server, Mercurial. Сегодня познакомимся и погорим о Git — [самой популярной](https://survey.stackoverflow.co/2022/#version-control-version-control-system) системой, ей пользуются более 90% разработчиков.

Git появился 7 апреля 2005 года и был создан для управления разработкой ядра Linux. Кстати, создал его тот самый [Линусом Торвальдсом](https://ru.wikipedia.org/wiki/%D0%A2%D0%BE%D1%80%D0%B2%D0%B0%D0%BB%D1%8C%D0%B4%D1%81,_%D0%9B%D0%B8%D0%BD%D1%83%D1%81), а сегодня его развитием и поддержкой занимается [Джунио Хамано](https://ru.wikipedia.org/wiki/%D0%A5%D0%B0%D0%BC%D0%B0%D0%BD%D0%BE,_%D0%94%D0%B6%D1%83%D0%BD%D0%B8%D0%BE).

Git — это распределённая система управления версиями. 

Что такое распределенная система: есть один сервер, через который разработчики обмениваются кодом. Разработчик копирует (клолнирует) проект к себе на локальную машину, делает изменения и сохраняет их на удаленный сервер. При необходимости, другие разработчики могут скопировать эти изменения к себе.

Почти все разработка ведется локально, ведь история и копия проекта хранится локально и чаще всего не нужна никакая дополнительная информация с других клиентов. Вы можете работать с репозиторием и при отсутствии интернета (например, в самолете), а когда он появится, просто загрузить изменения в удаленный репозиторий (тот что на выделенном сервере).

Если у разработчика сломается компьютер, то проект не потеряется - он сохранен на выделенный сервер.

Такой выделенный сервер, можно [поднять и настроить самому](https://about.gitlab.com/), а можно использовать существующие сервисы.

**GitHub** - крупнейший веб-сервис, который позволяет заниматься совместной разработкой  с использованием Git и сохранять изменения на своих серверах (на самом деле, [функциональность](https://github.com/about) GitHub намного больше, но сейчас нас интересует только совместная разработка).  

Еще есть [Gitlab](https://about.gitlab.com/), [Bitbucket](https://bitbucket.org/product/ru/guides/basics/bitbucket-interface) и другие, но мы будем использовать GitHub, как самый популярный в настоящее время.

## Предварительная настройка

Для начала немного подготовительной настройки.

Для начала ааарегистрируйтесь на GitHub](https://github.com/join?source=header-home) при регистрации задайте логин, почту и придумайте пароль. После “Создать аккаунт” не забудьте проверить почту и подтвердить ее (опрос от Github после подтверждения почты можно пропустить).

если все ок, экран GitHub будет выглядеть вот так 

![Untitled](img/Untitled.png)

В GitHub есть разграничение прав на репозитории. Можно задавать различные политики для репозитория: сделать публичным и [приватны](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/managing-repository-settings/setting-repository-visibility)м, ограничить права кругу пользователей или кому то одному, например, разрешить просматривать репозиторий, но не изменять в нем данные.

 Для того, что бы сервис определил кто вы и имеете ли право работать с тем или иным репозиторием  нужно представиться - пройти процесс [аутентификации](https://ru.wikipedia.org/wiki/Аутентификация).

Для безопасной работы GitHub поддерживает два сетевых протокола [HTTPS](https://ru.wikipedia.org/wiki/HTTPS) и [SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh) и вся работа с сервисом происходит через один из них.

Работать с GitHub будем через терминал по SSH. Для этого мы один раз сгенирируем специальный ключи, добавим один из них в наш аккаунт на GitHub.

Можно работать и через HTTPS, но нужно будет каждый раз вводить пароль и специальный [token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token).

Пара слов про SSH и как он работает.

SSH - это сетевой протокол для зашифрованного соединения между клиентом и сервером → данные по такому соединения можно передавать безопасно.

При установлении соединения используется пара ключей: открытый (публичный, *public*) и закрытый (приватный, *private).* Пользователь создает пару ключей при помощи специальной команды и сохраняет закрытый ключ у себя, а открытый “кладет” на сервер (в нашем случае на GitHub). А работает это все благодаря [ассиметричному шифрованию.](https://ru.wikipedia.org/wiki/Криптосистема_с_открытым_ключом)

Алгоритм работает так: отправитель (GitHub) шифрует сообщение публичным ключом и передает сообщение клиенту (нам), а мы его расшифровываем при помощи приватного ключа, который предусмотрительно сохранили у себя. То что зашифровано публичным ключом, расшифровать сможет только приватный ключ. 

Давай-те создадим пару ключей и добавим открытый ключ на GitHub

Что-бы создать пару ключей, в терминале нужно ввести команду, задать путь где сохранить ключи и задать пароль к ключу (не обязательно).

Будем дальше в статье основываться на том, что путь для ключей дефолтный и пароль на ключи не установлен.

Пароль для ключей нужен, как дополнительная мера безопасности, если вдруг ваш приватный ключ попадёт не в те руки.

```python
$ ssh-keygen
Generating public/private rsa key pair.
# путь до ключей, в скобках путь по умолчанию
Enter file in which to save the key (/Users/ifireice/.ssh/id_rsa):  
# пароль для ключей, при задании пароля в консоли не отображается ничего, даже звездочки
# если нажать Enter ничего не вводя, пароль будет пустым
Enter passphrase (empty for no passphrase):
# повторите пароль
Enter same passphrase again:
# после появится сообщение такого вида
Your identification has been saved in /Users/ifireice/.ssh/id_rsa
Your public key has been saved in /Users/ifireice/.ssh/id_rsa.pub
The key fingerprint is:
SHA256:Zu+HkZPC4ZP0veRmVjuKgylVvljHBNO8mHs+ieFFPvs ifireice@ifireice-osx
The key's randomart image is:
+---[RSA 3072]----+
|           o     |
|          o o    |
|           = .   |
|        o + +    |
|       +S* X     |
|       oB.@ X .  |
|       . O.# * . |
|      . +.*.% o  |
|       .  o*.+E. |
+----[SHA256]-----+
```

Вуаля, ключи сгенирированы (в заданной директории появится 2 файла `id_rsa` и  `id_rsa.pub`).

Теперь надо добавить публичный ключ в аккаунт на GitHub.

```python
# выведите содержимое публичного ключа в консоль
$ cat ~/.ssh/id_rsa.pub 
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQDDJfHIi73sKd6cqm3RwKuY1zl46aAaE6X9Gp
/6zJiY3BiJj95oJjPdpfpPhVFWLIbmT8zFAtOLbX9N4C3b0enHUzgMacP/Kl4AbrAkhLqaua9iD
VNxxiTVxADG1M5525oc/eAvx7y0pXIb9ouWdYJSKa8/TUYFhWlCzV2quY9SA0FaMs7eY41+KWYpG.....
tA0oGxv+7WmXQmQzleLIRG13KQ+VAbL2vabdPcRoGuZavh0smOr/GtVSnLdspZ5RgONMSPWlF2I1YHMR
Q7CIKPs= ifireice@ifireice-osx
$
```

Скопируйте ключ от символов `ssh-rsa` и до конца файла и вставьте его в ваш аккаунт на GitHub. Идем в  иконка пользователя (1) → Settings (2) 

![Untitled](img/Untitled%201.png)

→ SSH and GPG keys (3) → New SSH key (4)

![Untitled](img/Untitled%202.png)

→ в **Title** дайте имя ключу, что бы понимать откуда он (мб в будущем, у вас будет несколько ключей) (5) → в **Key** вставляем скопированный из консоли ключ (6) → жмяк кнопку Add SSH key (7)

![Untitled](img/Untitled%203.png)

После этого в ваших SSH ключах появится новый ключ и с компьютера где лежит приватный ключ сможете работать с GitHub

![Untitled](img/Untitled%204.png)

Ну что, с настройкой GitHub пока закончили, осталось установить `git` на компьютер. Сделать это можно по [официальной](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) инструкции (выберете пункт для вашей ОС).

======


## Терминология

Немного терминологии, прежде чем начнем создадим первый PR.

**Репозиторий** (repository)- директория проекта, который отслеживается Git. В директории хранится проект, история изменений и мета информация проекта (в скрытой директории `.git`)

**Индекс** - такая хранилка, в которой содержатся имена файлов и изменения в них, которые должны быть в следующем коммите. По факту индекс просто файл. В индекс файлы сами не попадают, их нужно явно добавлять при помощи `git add`

**Коммит** (commit) - это фиксация изменений в истории проекта (изменения, которые внесены в индекс). Коммит хранит измененные файлы, имя автора коммита и время, в которое был сделан коммит + каждый коммит имеет уникальный идентификатор, который позволяет в любое время к нему откатиться.

**Ветка** (branch) - последовательность коммитов. По сути это ссылка на последний коммит в этой ветке. Ветки не зависят друг от друга, можно вносить изменения в одну ветки и они не повлияют на другую ветку (если вы явно этого не попросите). Изначально одну ветка  - **main**, чуть позже увидим.

**Пул реквест** - pull request PR (пиар) (он же merge request MR(мр)) - 

**Форк** (Fork) - 

 

====

## Начало работы

Начнем с простого - создадим свой репозиторий и сделаем наш первый коммит.

Открываем repositories (1) и создаем новый (2).

![Untitled](img/Untitled%205.png)

Зададим параметры:

- (1) Repository name: имя нашего репозитория
- (2) Description: описание репозитория
- (3) [Тип репозитория](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/managing-repository-settings/setting-repository-visibility): Public (публичный) или Private (приватный). Сейчас выберем публичный - кто угодно может видеть содержимое репозитория.
- (4) Ставим галку создать README файл. В этом файле в формате [MarkDown](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)  описывают проект или различную документацию.  Именно содержимое этого файла можно увидеть, когда заходим на главную страницу репозитория. Пример [1](https://github.com/prometheus/prometheus), [2](https://github.com/django/django), [3](https://github.com/ohmyzsh/ohmyzsh).
- (5) Если мы знаем на каком языке наш проект, можем добавить шаблон `.gitignore` для этого языка. Сейчас у нас нет какого то языка, мы не будем создавать `.gitignore`.
- (6) Выбираем [тип лизенции](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository) для нашего кода. В лицензии оговариваются права на проект. Стоит обратить внимание на [BSD 3](https://opensource.org/licenses/BSD-3-Clause) или [MIT](https://opensource.org/licenses/MIT), тк они предоставляют хороший баланс прав и ответственности.
- (7) По умолчанию имя основной ветки в GitHub носит имя `main`, но до [недавнего времени](https://www.theserverside.com/feature/Why-GitHub-renamed-its-master-branch-to-main) имя было `master` .

![Untitled](img/Untitled%206.png)

И нажимаем кнопку “Create repository”.  Успех, у нас есть первый репозиторий!

![Untitled](img/Untitled%207.png)

### А что будет, если не добавим README и .gitignore?

На самом деле ничего страшного не произойдет, но придется выполнить еще ряд шагов, что бы [проинициализировать](https://git-scm.com/docs/git-init) git-репозиторий, прежде чем начать с ним работать. 

Не переживайте, Git очень дружелюбный и расскажет как это сделать.

![Untitled](img/Untitled%208.png)

Ну что, мы создали репозиторий на удаленном сервере, самое время “забрать” его к себе на локальную машину и внести какие-то изменения.

Что бы “забрать” репозиторий его надо склонировать к себе при помощи команды `git clone` и пути до репозитория.

Для начала получим путь до репозитория.

Для этого заходим в созданный репозиторий и находим кнопочку “Code” (1) → нажимаем ее → выбираем SSH (2) → и копируем строку (3)

![Untitled](img/Untitled%209.png)

Теперь идем в консоль, переходим в директорию где хотим хранить проекты и выполним (`git@github.com:ifireiceya/MyFirstRepo.git` - путь который мы скопировали ранее)

```python
$ git clone git@github.com:ifireiceya/MyFirstRepo.git
Cloning into 'MyFirstRepo'...
remote: Enumerating objects: 4, done.
remote: Counting objects: 100% (4/4), done.
remote: Compressing objects: 100% (4/4), done.
remote: Total 4 (delta 0), reused 0 (delta 0), pack-reused 0
Receiving objects: 100% (4/4), done.
```

Переходим в новый каталог, в котором теперь лежит копия нашего проекта с GitHub

```python
$ cd MyFirstRepo
```

Можем посмотреть, что у нас в этой директории уже есть 

```python
$ ls -a
.git      LICENSE   README.md
```

Мы видим два знакомых нам файла `LICENSE` и `README.md`, а так же одну скрытую директорию `.git`

В `.git` хранится мета информация проекта и вся история для проекта. На каждый проект есть только одна директория .git и  лежит она в корне проекта. 

```python
$ ls .git
HEAD                 # указатель на вашу активную ветку
config               # персональные настройки для проекта
description          # описание проекта
hooks                # pre/post action hooks
index                # индексный файл
logs                 # история веток проекта (где они располагались)        
objects              # ваши объекты (коммиты, теги и тд)
packed-refs refs     # указатели на ваши ветки разработки
```

Давайте немного поднастроим git под себя - делаем только один раз, потом настройки сохраняться, но при необходимости их можно изменить.

При установке Git была установлена утилита `git config` , которая позволяет просматривать и изменять большинство параметров работы Git’а

Будь-то данные пользователя или способ работы репозитория – это самый удобный способ настройки.

Настроим имя пользователя и адрес электронной почты. Эта информация важна, потому что она включается в каждый коммит.

Для этого в терминале переходим в git репозиторий для которого задаем настройки и выполняем:

```python
$ git config user.name "Дарья Меленцова"
$ git config user.email ifireice@example.com

# Если добавить опцию --global, то эти настройки запишутся в настройки пользователя и будут действовать на все проекты. 
# Мы выполняем эту команду без параметра --global, чтобы настройки касались только вашего проекта.
```

Что еще можно настроить с помощью `git config` читать [тут](https://git-scm.com/docs/git-config).

### Вносим изменения

Теперь нам нужно внести изменения в наш проект. 

Но перед этим посмотрим 2 полезных команды:

- `git status` - показывает текущее состояние файлов в репозитории (какие файлы изменились, удалились, добавились)
- `git log` - показывает историю изменений ( это про зафиксированные изменения - коммиты (commit))

Выполним эти команды  и посмотрим, что они выведут для нашего репозитория.

 `git status` видим, что у нас нет изменений - коммитов в репозитории ( мы ведь только его склонировали и еще ничего не делали)

```python
$ git status                                  
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

а `git log` покажет нам, что в проекте был только один Initial commit - когда мы создавали репозиторий с README.md

```python
$ git log
commit 9ae1cbcc77f3b64d604612d4a599bdbb8b1cf204 (HEAD -> main, origin/main, origin/HEAD)
Author: ifireiceya <117034707+ifireiceya@users.noreply.github.com>
Date:   Mon Oct 31 00:01:05 2022 +0300

    Initial commit
(END)
```

Убедились, что у нас нет неучтенных изменений, пора бы уже что-то сделать.

Открывайте любимый текстовый редактор и создаем новый файл с именем hw.py.

Это будет небольшая программа на Python, которая при запуске печатает “Hello World!”

```python
$ vi hw.py
print("Hello World!")

```

Отлично, код написан и даже в есть локально в нашем репозитории (мы же в директории проекта все делали)

Итак наша задача сохранить наши изменения в “оригинальный”(удаленный) репозиторий. Для этого нам нужно:

1. Познакомить Git с новым файлом - добавить файл в индекс - `git add`
2. Зафиксировать изменения “закоммитить” - `git commit`
3. Синхронизировать наши изменения с серверов - `git push`
4. Посмотреть в репозиторий и убедится, что все сработало

Делаем:

Мы уже создали файл, посмотрим в каком теперь у нас статусе Git

![Untitled](img/Untitled%2010.png)

Мы видим, что появился файл `hw.py`, но он красный. Паника! Все сломалось?!

Все в порядке, но прежде чем продолжить, стоит обсудить состояние файлов с точки зрения Git’а.

По мнению Git’а файл может в одним из четырех состояний:

1. Неотслеживаемый (*untracked*)

1. измененный (modified) - файл, в котором есть изменения, но он еще не добавлен в коммит (не зафиксирован)
2. отслеживаемый (staged) - файл, который добавили в индекс
3. зафиксированный (committed) - файл уже сохранен в локальной базе и в нем не было изменений с последнего коммита.

![Untitled](img/Untitled%2011.png)

В связке с состоянием файлов есть три основных секции проекта.               

- рабочая директория (working directory) - это директория которая содержит в себе то с чем вы работаете или то что вы извлекли из истории проекта в данный момент. рабочая директория это просто временное место где вы можете модифицировать файлы, а затем выполнить коммит.
- область индексирования (staging area) - индекс - файл, в каталоге Git, который содержит информацию о том, что попадет в следующий коммит.
- каталог Git -  место, где Git хранит метаданные и базу объектов вашего проекта, помните еще про `.git`?

На практике: 

Мы добавили новый файл [hw.py](http://hw.py) и видим, что у него состояние *untracked, т.е.* не важно что мы делаем с файлом, Git проигнорирует любые изменения в нем.

Для того, что бы Git начал “следить” за изменениям в файле, его нужно добавить в индекс. 

Для этого используем команду `git add <имя файла>` 

Кстати, заметили, что Git довольно дружелюбный и часто подсказывает команды, который нужно выполнить

```python
$ git add hw.py
# если нужно добавить много файлов и не хочется описывать, можно использовать команду
# git add .
# но стоит точно понимать, что добавляем, иначе придется удалять потом файлы из индекса
# кстати, для удаления используется команда git rm ,но стоит почитать доку перед использованием
```

И еще не забывайте о файле `.gitignore` в котором перечисляем папки и файлы репозитория, которые Git не должен отслеживать и синхронизировать их состояние (не добавлять их в индекс). Обычно в него добавляют файлы логов, результаты сборки и тд. Поддерживает [шаблоны](https://git-scm.com/docs/gitignore).  

`.gitignore` то же файл, который надо добавить в индекс.

Если файл попадает в “правила” `.gitignore`, то он не появится в `git status`

Если файл был добавлен в индекс, а потом добавлено правило для файла в `.gitignore` - файл все равно будет отслеживаться и его надо явно [удалить](https://git-scm.com/docs/git-rm) из индекса.

Посмотрим как изменилось состояние нашего файла

```python
$ git status
```

![Untitled](img/Untitled%2012.png)

О, наш файл стал зеленым и сообщение от Git изменилось. Кстати, файл теперь имеет состояние *staged*.

Хотим зафиксировать изменения, тк наша задача сейчас решена - мы написали программку на Python и хотим сказать Git, что вот сейчас мы закончили работать с файлом и надо запомнить текущее состояние. 

Для этого на нужно закомитить файл и поможет команда `git commit` 

При создании принято писать описание коммита и делается это с помощью ключа `-m`

```python
$ git commit -m "add python hello world"     
[main 6d8a5c3] add python hello world
 1 file changed, 1 insertion(+)
 create mode 100644 hw.py
```

Пара слов про то как писать сообщения для коммитов:

- максимум 50 символов
- осознано и понятно, как будто пишете для человека, который по описанию должен понять, что происходит внутри коммита, ведь этим человеком через какое то время можете стать вы, а о себе надо заботиться
- сообщение стоит начинать с заглавной буквы
- если меняли код пишите исходный код в сообщении

```python
$ git log
```

![Untitled](img/Untitled%2013.png)

Осталось отправить наши изменения на  “удаленный” сервер. Используем `git push`

```python
$ git push
Counting objects: 100% (4/4), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 341 bytes | 341.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
To github.com:ifireiceya/MyFirstRepo.git
   9ae1cbc..6d8a5c3  main -> main
```

Предлагаю проверить, что наши изменения есть на GitHub. Идем в репозиторий и смотрим на него → видим, что появился наш файл и даже видим нам commit message, которы задали.

![Untitled](img/Untitled%2014.png)

## Задача немного посложнее

Все здорово, но мы не всегда создаем репозитории и часто нам нужно добавлять новые фичи или исправления в уже существующий репозиторий, да еще и не наш.

Например, есть у нас наш любимый опенсорсный проект, в который мы хотим причинить добро и закрыть им какой нибудь [Issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/about-issues).

В учебных целях у нас есть репозиторий этой статьи на GitHub и мы хотим исправить опечатку, которую нашли в статье.

Но будем делать это как будто не наш репозиторий, а мы внешние пользователи. 

Репозиторий хранится в `ifireice/git` , а изменения у нас делает пользователь `ifireiceya`


#TODO
Дописать 
- squash - схлапывание коммитов в один 
- revert
- rebase
- cherry-pick
