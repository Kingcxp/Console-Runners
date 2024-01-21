## 我是怎么做出ConsoleRunners的
#### By Kingcq

### 前置知识
#### 字符集编码方式
&emsp;&emsp;在 C/C++ 语言标准中定义了其运行时的字符集环境为 "C" ，也就是 ASCII 字符集的一个子集。而这个字符集通常并不能完整地表示我们平时需要用到的一些字符，比如我们游戏中小人的头'○'就会被显示成'?'
&emsp;&emsp;那怎么解决这个问题呢？C 语言标准库<locale.h>当中为我们准备了`setlocale`这个方法来帮助我们调整程序的本地化设置。
&emsp;&emsp;在我写的这个游戏中，我们始终使用 en_US.UTF-8 字符集来编写，大部分常用的命令行环境都是支持的，至少到目前为止，除了一些字符仍然无法正常显示以外，我还没有遇到任何的与环境有关系的问题。（了解下来问题其实可能还蛮大的，但是以我周围大部分人的环境不会有任何的问题）
&emsp;&emsp;设置起来非常方便，只需要一行就好。
```c
setlocale(LC_ALL, "en_US.UTF-8");
```

#### 输入和输出控制，掌控命令行的每个字符
&emsp;&emsp;读取键盘键入这个事应该很多人都知道，Windows 下有一个 C 库叫<conio.h>，它里面的方法（`kbhit`）能够很轻易地判断出当前有没有键入，以及读入一个键盘输入（`getch`）。这个操作在 Windows 环境下很容易做到，但是在 Unix 命令行环境当中，情况有所不同，这个库并不是 C 的标准库，除了 Windows 其它平台并没有，这怎么办呢？
&emsp;&emsp;实际上通过搜索就能够找到很多的解决方案，但是有不少实际执行起来有点问题，不符合实际需要，我在这里就把经过我挑出来的方案放出来。
```c
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <unistd.h>

    static struct termios initial_settings, new_settings;
    static int peek_character = -1;
#endif
// 判断是否有键入
int keyboardHit() {
    #ifdef _WIN32
        return kbhit();
    #else
        char ch;
        int nread;
        if(peek_character != -1) {
            return 1;
        }
        new_settings.c_cc[VMIN] = 0;
        tcsetattr(0, TCSANOW, &new_settings);
        nread = read(0, &ch, 1);
        new_settings.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &new_settings);
        if(nread == 1) {
            peek_character = ch;
            return 1;
        }
        return 0;
    #endif
}
// 读取单个键入字符
int termGetch() {
    #ifdef _WIN32
        return getch();
    #else
        char ch;
        if(peek_character != -1) {
            ch = peek_character;
            peek_character = -1;
            return ch;
        }
        read(0, &ch, 1);
        return ch;
    #endif
}
// 初始化终端环境，\033字符的事情之后再说
void initConsole() {
    #ifndef _WIN32
        // init keyboard
        tcgetattr(0, &initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_lflag &= ~ISIG;
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &new_settings);
    #endif
    setlocale(LC_ALL, "en_US.UTF-8");
    wprintf(L"\033[?25l\033[1;1H\033[2J");
}
// 结束终端环境
void endConsole() {
    #ifndef _WIN32
        // close keyboard
        tcsetattr(0, TCSANOW, &initial_settings);
    #endif
    wprintf(L"\033[?25h\033[1;1H\033[2J");
}
```

#### \033 ANSI 屏幕控制码
&emsp;&emsp;在终端中，ANSI定义了用于屏幕显示的Escape屏幕控制码，在printf函数调用时可以输出具有颜色的字符，这个特性对于绝大部分终端都是有效的，因此我们借助这个方法能够实现很多东西。
比如上面的`\033[?25l`和`\033[?25h`就分别代表隐藏和显示光标，`\033[y;xH`代表将光标移动到第y行第x列处（从1开始），`\033[2J`表示清屏。
&emsp;&emsp;借助`\033`我们能够定义一些基础的实用小方法：
```c
// 设置光标位置（我的光标位置是从0开始算的，所以要加一）
void setCursor(const int x, const int y) {
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}
// 大部分终端都支持的颜色（注意！部分颜色在不同终端中表现不相同）
typedef enum Color {
    Color_Escape,
    Color_Black,
    Color_DarkGray,
    Color_BlackUnderline,
    Color_BlackBlink,
    Color_Blue,
    Color_LightBlue,
    Color_BlueUnderline,
    Color_BlueBlink,
    Color_Green,
    Color_LightGreen,
    Color_GreenUnderline,
    Color_GreenBlink,
    Color_Cyan,
    Color_LightCyan,
    Color_CyanUnderline,
    Color_CyanBlink,
    Color_Red,
    Color_LightRed,
    Color_RedUnderline,
    Color_RedBlink,
    Color_Purple,
    Color_LightPurple,
    Color_PurpleUnderline,
    Color_PurpleBlink,
    Color_Brown,
    Color_Yellow,
    Color_YellowUnderline,
    Color_YellowBlink,
    Color_LightGray,
    Color_White,
    Color_GrayUnderline,
    Color_GrayBlink,
} Color;
const wchar_t *ANSI_Colors[] = {
    L"\033[0m",
    L"\033[0;30m",
    L"\033[1;30m",
    L"\033[4;30m",
    L"\033[5;30m",
    L"\033[0;34m",
    L"\033[1;34m",
    L"\033[4;34m",
    L"\033[5;34m",
    L"\033[0;32m",
    L"\033[1;32m",
    L"\033[4;32m",
    L"\033[5;32m",
    L"\033[0;36m",
    L"\033[1;36m",
    L"\033[4;36m",
    L"\033[5;36m",
    L"\033[0;31m",
    L"\033[1;31m",
    L"\033[4;31m",
    L"\033[5;31m",
    L"\033[0;35m",
    L"\033[1;35m",
    L"\033[4;35m",
    L"\033[5;35m",
    L"\033[0;33m",
    L"\033[1;33m",
    L"\033[4;33m",
    L"\033[5;33m",
    L"\033[0;37m",
    L"\033[1;37m",
    L"\033[4;37m",
    L"\033[5;37m",
};
```

有了这些前置知识，编写游戏的所有工具就齐了，接下来就是代码框架和游戏结构的设计。

### 卑微的开始

&emsp;&emsp;基本的游戏逻辑，无论是图形界面还是纯文本界面，我觉得实际上都是几乎完全一致的，游戏的一次刷新作为一帧，计算出这一帧过去的时间和发生的所有事件，并借助这些数据进行处理，随后处理输出图像。只不过纯文本的事件处理更加简单，仅仅包含键盘按键的读入作为事件。

&emsp;&emsp;所以我们凭借着这样的理解和上面准备好的小工具，很容易能写出主函数当中的内容（事件处理、更新、绘制在之后会提到，在这里略过）：
```c
int main(int argc, char *argv[]) {
    initConsole();

    bool loop = true;
    clock_t now = clock();

    while (loop) {
        int ch = 0;
        while (keyboardHit()) {
            ch = termGetch();
            // 在这里根据 ch 处理事件
        }
        // 计算过去的时间
        float deltaTime = (float)(clock() - now) / (float)CLOCKS_PER_SEC;
        now = clock();
        // 根据事件更新游戏状态

        // 在这里绘制游戏画面
    }

    endConsole();
    return EXIT_SUCCESS;
}
```

### C 语言的面向对象
&emsp;&emsp;一个相对复杂的游戏的帧逻辑过程一定也是复杂的，你真的想把所有的东西全部都塞在 `main.c` 这一个文件里面吗？那一定非常的难看吧！这对于代码的编写和修改都是极为致命的——你的脑袋根本装不下这么多的代码！
&emsp;&emsp;那你紧接着肯定就会想到，我把这些代码按照含义分开成多个文件，然后再 include 进来，这不就好了吗？这种做法的确非常有效，但是仍然非常的耗脑子，对于某一个“物体”，比如一个按钮，或者一个人物，有很多个变量都和他们相关，你可能需要在多个文件里同时追踪这许多变量，这可太难做到了！
&emsp;&emsp;那么，有没有更好的办法，能够让我们能够专注于“物体”本身，将它的属性全部收纳到一起，将追踪“属性”转变为更简单的追踪“物体”呢？
&emsp;&emsp;这就是面向对象的思路——对数据进行“降维打击”，从更高的层面去专注于“物体”本身，而不是它的每一个“属性”。
&emsp;&emsp;要说把很多种数据组合在一起，那么 C 语言当中我们只有可能想到一种类型：struct 结构体。那我们可以写出类似于这样的代码：
```c
// 记录一个盒子的长宽高和重量
typedef struct Box {
    int h, w, d, weight;
} Box;
// 一个人，手中可能抱了盒子，最大能抓住多重的盒子
typedef struct Person {
    int bearing;
    Box *boxInHand;
} Person;
```
&emsp;&emsp;这个时候，我们如果想让一个`Person`抱起一个`Box`，我们需要这样写：
```c
if (person.bearing >= box.weight && person.boxInHand == NULL) {
    person.boxInHand = &box;
}
```
&emsp;&emsp;这实际上还是略显复杂了，想象现在有一个非常复杂的“搬运”过程，你要用这种形式在各处需要“搬运”的地方都写上吗？还是老问题，我们没有专注于“物体”本身，而是仍然将“物体”拆分为单个数据在处理。
&emsp;&emsp;实际上我们更想要写出这样的代码：
```c
person.carry(&box);
```
&emsp;&emsp;但是 C 语言并不允许我们在结构体里面塞函数，只能塞变量和指针，这怎么办才好呢？
&emsp;&emsp;实际上答案已经呼之欲出了，那就是使用函数指针，并且我们在创建`Person`实例的时候需要将对应的函数赋给它，这意味着我们需要重新自定义`Person`物体的创建过程，从这样的做法为之后的编程带来的便利来看，这一点牺牲实际上是非常赚的：
```c
typedef struct Person {
    void (*carry)(struct Person *p, Box *box);
    int bearing;
    Box *boxInHand;
} Person;

void Person_carry(Person *p, Box *box) {
    if (p->bearing >= box->weight && p->boxInHand == NULL) {
        p->boxInHand = &box;
    }
}

Person *createPerson() {
    Person *p = (Person *)malloc(sizeof(Person));
    p->carry = Person_carry;
    return p;
}

void destroyPerson(Person *p) {
    free(p);
}
```
&emsp;&emsp;我们通常把一个类分成一个文件存储，在这里我们可以将这个类存为`Person.h`，并为它两边加上这样的定义以避免多次定义：
```c
// 如果没有定义过 Person
#ifndef PERSON
// 定义 Person 并做接下来的事
#define PERSON
// 上面的代码写在这里
#endif // 结束上面的 ifndef 条件语句
```

### 坏了！它们俩怎么互相需要啊？
&emsp;&emsp;人能把盒子抱起来，有的时候，盒子也能装人。
&emsp;&emsp;在这种情境下，`Person.h`需要 #include "`Box.h`"，而`Box.h`需要 #include "`Person.h`"。
&emsp;&emsp;这坏了！`Person.h`需要`Box.h`，`Box.h`里包含`Person.h`就又会把`Person.h`拿过来……如此递归调用，虽然我们之前的操作能够避免重复定义，但是这两个文件最后总得分个先后，总有一个会拿不到另一个的定义。
&emsp;&emsp;这可怎么办呢？我们可以先声明，再调用。我们发现`Person.h`里并不需要 `Box` 真实存在，我们只需要知道有这么个东西就行，那我们可以只声明有 `Box` 这个东西，但是不说它到底是什么，等到之后再说。
&emsp;&emsp;所以，取消`Person.h`包含`Box.h`的行为，而替换为`typedef struct Box Box;`，代码仍然可以正常运行。
&emsp;&emsp;等等，真的能正常运行吗？如果你真的去试了，你就会发现并不行。
&emsp;&emsp;仔细看，在 `carry` 方法中，我们用到了 `Box` 的属性，而此时 `Box` 还没有给出定义，仅仅只是一个不完整的指针，C 语言不知道这个属性到哪里去找，所以这样仍然没有办法编译成功。
&emsp;&emsp;那难道就没有别的办法了吗？当然有！我们将定义和实现拆开，`Person.h` 当中只留下定义，也就是这样：
```c
// Person.h
#ifndef PERSON
#define PERSON
typedef struct Person {
    void (*carry)(struct Person *p, Box *box);
    int bearing;
    Box *boxInHand;
} Person;

Person *createPerson();
void destroyPerson(Person *p);
#endif // PERSON
```
&emsp;&emsp;剩下的实现，我们挪到新文件 `Person.c` 里面：
```c
// Person.c
#include "Person.h"
#include "Box.h"

void Person_carry(Person *this, Box *box) {
    // ...
}
Person *createPerson() {
    // ...
}
void destroyPerson(Person *p) {
    // ...
}
```
&emsp;&emsp;看到了吗？我们可以在实现的时候，需要用到 `Box` 了，再给出 `Box` 的具体定义，实现可以放到所有代码的最后再给出，这个时候，该定义的都定义好了，就不会出现递归包含的问题了。
&emsp;&emsp;实现只应该也只能被包含一次，而定义可以被包含多次（同时为了代码补全和解决递归包含），这种基本的面向对象结构将会贯穿我们的整个项目，请务必记好。
