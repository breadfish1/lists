#include <iostream>

struct object {
    char name[30];
    char address[30];
    int operator == (object x) {
       return (!strcmp(x.name, name) && !strcmp(x.address, address));
    }
};

namespace arr { // массив
    typedef int position;
    
    struct element {
        object o;
        position ps;
        element() { o.name[0] = '\0'; o.address[0] = '\0';  ps = -100;}
    };
    
    static const element F;
    
    void prn(object o) {
        std::cout << o.name << " " << o.address;
    }
    
    class lst {
    public:
        lst();
        int full() const; // проверка полноты
        int empty() const; // проверка пустоты
        position END(); // возвращает следующую позицию после последнего
        void INSERT(object x, position p); // вставить x в позиции p
        position LOCATE(object x); // поиск x в списке, возвращает позицию, если объекта нет, то возв. END();
        object RETRIEVE(position p); // возвращает объект по позиции p, результат неопределен, если p = END();
        void DELETE(position p); // удалить элемент в позиции p
        position NEXT(position p); // следующая позиция после p
        position PREVIOUS(position p); // предыдущая позиция перед p
        void MAKENULL(); // делает список пустым
        position FIRST(); // возвращает первую позицию, если список пуст, то возвращает END();
        void PRINT(); // печать списка
    private:
        position end();
        void insert(object x, position p);
        position locate(object x);
        object retrieve(position p);
        void del(position p);
        position next(position p);
        position previous(position p);
        void makenull();
        position first();
        void print();
        static const int SIZE = 10;
        object s[SIZE];
        int up; // последний заполненный
    };
    
    lst::lst() {
        up = -1;
    }
    
    int lst::empty() const {
        return up == -1;
    }
    
    int lst::full() const {
        return up == SIZE - 1;
    }
    
    position lst::end() { // up - последний занятый
        return up + 1;
    }
    
    void lst::insert(object x, position p) {
        if (up < SIZE - 1) {
            for (int i = p; i < up; i++)
                s[i + 1] = s[i];
            s[p] = x;
            up++;
        }
        else {
            std::cout << "There's no space\n";
        }
    }
    
    position lst::locate(object x) {
        for (int i = 0; i <= up; i++) // если нашли такой элемент, то возвращаем позицию, иначе -1
            if (x == s[i])
                return i;
        return end();
    }
    
    object lst::retrieve(position p) {
        if (p > -1 && p <= up)
            return s[p];
        
        return F.o;
    }
    
    void lst::del(position p) {
        if (p > -1 && p <= up) {
            for (int i = p; i < up; i++)
                s[i] = s[i + 1];
            up--;
        }
    }
    
    position lst::next(position p) {
        if (p == up)
            return end();
        if (p > up)
            return F.ps;
        return up + 1;
    }
    
    position lst::previous(position p) {
        if (p == 0 || p > up + 1)
            return F.ps;
        return p - 1;
    }
    
    void lst::makenull() {
        up = -1;
    }
    
    position lst::first() {
        return 0;
    }
    
    void lst::print() {
        for (int i = 0; i <= up; i++)
            std::cout << s[i].name << " " << s[i].address << std::endl;
    }
    
    position lst::END() {
        return end();
    }
    
    void lst::INSERT(object x, position p) {
        insert(x, p);
    }
    
    position lst::LOCATE(object x) {
        return locate(x);
    }
    
    object lst::RETRIEVE(position p) {
        return retrieve(p);
    }
    
    void lst::DELETE(position p) {
        del(p);
    }
    
    position lst::NEXT(position p) {
        return next(p);
    }
    
    position lst::PREVIOUS(position p) {
        return previous(p);
    }
    
    void lst::MAKENULL() {
        makenull();
    }
    
    position lst::FIRST() {
        return first();
    }
    
    void lst::PRINT() {
        print();
    }
}

namespace list_1connection { // односвязный список
    struct element;
    typedef element *position;
    
    struct element {
        element(object c, element *pos) : o(c), ps(pos) {}
        element() { o.name[0] = '\0'; o.address[0] = '\0';  ps = this; }
        position ps;
        object o;
    };
    
    static const element F;
    
    class lst {
    public:
        lst();
        ~lst();
        int full() const;
        int empty() const;
        position END();
        void INSERT(object x, position p);
        position LOCATE(object x);
        object RETRIEVE(position p);
        void DELETE(position p);
        position NEXT(position p);
        position PREVIOUS(position p);
        void MAKENULL();
        position FIRST();
        void PRINT();
    private:
        int check(position p);
        position AddHead(position h, object x);
        position ClearList(position h);
        position DeleteHead(position h);
        void AddAfter(object x, position p);
        position end();
        position PreElement(position p);
        void insert(object x, position p);
        position locate(object x);
        object retrieve(position p);
        void del(position p);
        position next(position p);
        position previous(position p);
        position first();
        void print();
        position head;
    };
    
    int lst::check(position p) { // возвращает 1, если такой адрес есть в списке, 2, если добавляем в конец, иначе ноль
        position temp = head;
        
        if (p == NULL)
            return 2;
        
        if (p == head)
            return 3;
        
        while (temp) {
            if (temp == head)
                return 1;
            temp = temp->ps;
        }
        
        return 0;
    }
    
    lst::lst() {
        head = NULL;
    }
    
    lst::~lst() {
        position p = head;
        while (head) {
            head = head->ps;
            delete(p);
            p = head;
        }
    }
    
    int lst::empty() const {
        return head == 0;
    }
    
    int lst::full() const {
        return 0;
    }
    
    position lst::AddHead(position h, object x) {
        position q = new element(x, h);
        return q;
    }
    
    position lst::ClearList(position h) {
        while(h != 0)
            h = DeleteHead(h);
        
        return NULL;
    }
    
    position lst::DeleteHead(position h) {
        position q = h->ps;
        delete h;
        return q;
    }
    
    void lst::AddAfter(object x, position p) {
        position q = new element(x, p->ps);
        p->ps = q;
    }
    
    position lst::end() {
        return NULL;
    }
    
    position lst::PreElement(position p) {
        position last = head, temp = last;
        
        while (last != p) {
            temp = last;
            last = last->ps;
        }
        
        return temp;
    }
    
    void lst::insert(object x, position p) {
        int c = check(p);
        
        if (!c) // если пользователь пытается добавить в несуществующую позицию
            return;
        
        if (empty()) { // если список пуст, то добавляем в голову
            if (c == 2) // при пустом списке пользователь сможет добавить только в конец, проверяем, что он делает это
                head = AddHead(head, x);
            return;
        }
        
        if (c == 2) // если нужно добавить в конец, но список не пустой
            AddAfter(x, PreElement(end()));
        
        if (c == 3)
            head = AddHead(head, x);
            
        if (c == 1) // если нужно добавить в определенную существующую позицию
            AddAfter(x, PreElement(p));
    }
    
    position lst::locate(object x) { // возвращает позицию, если объект найден. если нет, то NULL
        position temp = head;
        
        while (temp) {
            if (temp->o == x)
                return temp;
            temp = temp->ps;
        }
        
        return F.ps;
    }
    
    object lst::retrieve(position p) {
        position temp = head;
        
        while (temp) {
            if (temp == p)
                return temp->o;
            temp = temp->ps;
        }
        
        return F.o; // ненастоящий элемент
    }
    
    void lst::del(position p) {
        position last = head, temp = last;
        
        while (last) {
            if (last == p)
                break;
            temp = last;
            last = last->ps;
        }

        if (temp == head && last == head) { // если нужно удалить голову
            head = DeleteHead(head);
            return;
        }
        
        if (last != NULL) {
            position _temp = temp->ps; // удаляемое
            
            temp->ps = _temp->ps;
            delete _temp;
            
            return;
        }
    }
    
    position lst::next(position p) {
        if (check(p)) {
            if (p->ps)
                return p->ps;
            else
                return end();
        }
        
        return F.ps;
    }
    
    position lst::previous(position p) {
        position temp = head, prev = temp;
        
        while (temp != NULL && temp != p) {
            prev = temp;
            temp = temp->ps;
        }
        
        if (temp != NULL)
            return prev;
        
        return F.ps;
    }
    
    position lst::first() {
        if (head)
            return head;
        
        return end();
    }
    
    void lst::print() {
        position temp = head;
        
        while (temp) {
            std::cout << temp->o.name << " " << temp->o.address << std::endl;
            temp = temp->ps;
        }
    }
    
    position lst::END() {
        return end();
    }
    
    void lst::INSERT(object x, position p) {
        insert(x, p);
    }
    
    position lst::LOCATE(object x) {
        return locate(x);
    }
    
    object lst::RETRIEVE(position p) {
        return retrieve(p);
    }
    
    void lst::DELETE(position p) {
        return del(p);
    }
    
    position lst::NEXT(position p) {
        return next(p);
    }
    
    position lst::PREVIOUS(position p) {
        return previous(p);
    }
    
    void lst::MAKENULL() {
        ClearList(head);
        head = NULL;
    }
    
    position lst::FIRST() {
        return first();
    }
    
    void lst::PRINT() {
        print();
    }
}

namespace list_2connection { // двусвязный список
    struct element;
    typedef element *position;
    struct element {
        element(object c, position next, position prev) : o(c), psNext(next), psPrev(prev) {}
        element() { o.name[0] = '\0'; o.address[0] = '\0';  psNext = this; psPrev = this; }
        position psNext, psPrev;
        object o;
    };
    
    static const element F;
    
    class pair {
    public:
        position head, tail;
    };
    
    class lst {
    public:
        lst();
        ~lst();
        int full() const; // проверка полноты
        int empty() const; // проверка пустоты
        position END(); // возвращает следующую позицию после последнего
        void INSERT(object x, position p); // вставить x в позиции p
        position LOCATE(object x); // поиск x в списке, возвращает позицию, если объекта нет, то возв. END();
        object RETRIEVE(position p); // возвращает объект по позиции p, результат неопределен, если p = END();
        void DELETE(position p); // удалить элемент в позиции p
        position NEXT(position p); // следующая позиция после p
        position PREVIOUS(position p); // предыдущая позиция перед p
        void MAKENULL(); // делает список пустым
        position FIRST(); // возвращает первую позицию, если список пуст, то возвращает END();
        void PRINT(); // печать списка
    private:
        int check(position p, position head); // возвращает 1, если такой адрес есть в списке, 2, если добавляем в конец, 3, если в начало, иначе ноль
        position AddHead(position h, object x); // добавить в голову
        position AddTail(position t, object x); // добавить в хвост
        pair ClearList(pair l); // очистить список
        position DeleteHead(position h); // удалить голову
        position DeleteTail(position t); // удалить хвост
        void AddAfter(object x, position p); // добавить после p объект x
        position end();
        pair insert(object x, position p, pair l);
        position locate(object x, position head);
        object retrieve(position p, position head);
        pair del(position p, pair l);
        position next(position p, position head);
        position previous(position p, position head);
        position first(position head);
        void print(position head);
        pair HT;
    };
    
    lst::lst() {
        HT.head = NULL;
        HT.tail = NULL;
    }
    
    lst::~lst() {
        HT = ClearList(HT);
    }
    
    int lst::full() const {
        return 0;
    }
    
    int lst::empty() const {
        return HT.head == 0;
    }
    
    int lst::check(position p, position head) { // возвращает 1, если такой адрес есть в списке, 2, если добавляем в конец, 3, если в начало, иначе ноль
        position temp = head;
        
        if (p == NULL)
            return 2;
        
        if (p == head)
            return 3;
        
        while (temp) {
            if (temp == head)
                return 1;
            temp = temp->psNext;
        }
        
        return 0;
    }
    
    position lst::AddHead(position h, object x) {
        position q = new element(x, h, NULL);
        
        if (h)
            h->psPrev = q;
        
        return q;
    }
    
    position lst::AddTail(position t, object x) {
        position q = new element(x, NULL, t);
        
        if (t)
            t->psNext = q;
        
        return q;
    }
    
    pair lst::ClearList(pair l) {
        position p;
        
        while (l.head) {
            p = l.head;
            l.head = l.head->psNext;
            delete p;
        }
        
        l.head = NULL;
        l.tail = NULL;
        
        return l;
    }
    
    position lst::DeleteHead(position h) {
        position p = h->psNext;
        
        p->psPrev = NULL;
        delete h;
        
        return p;
    }
    
    position lst::DeleteTail(position t) {
        position p = t->psPrev;
        
        p->psNext = NULL;
        delete t;
        
        return p;
    }
    
    void lst::AddAfter(object x, position p) {
        position q = NULL;
        q->psNext = p->psNext;
        q->psPrev = p;
        p->psNext = q;
        (q->psNext)->psPrev = q;
        q->o = x;
    }
    
    position lst::end() {
        return NULL;
    }
    
    pair lst::insert(object x, position p, pair l) {
        int c = check(p, l.head);

        if (!c) // если пользователь пытается добавить в несуществующую позицию
            return l;

        if (empty()) { // если список пуст, то добавляем в голову
            if (c == 2) { // при пустом списке пользователь сможет добавить только в конец(или начало), проверяем, что он делает это
                l.head = AddHead(l.head, x);
                l.tail = l.head;
            }
            return l;
        }

        if (c == 2) { // если нужно добавить в конец, но список не пустой
            l.tail = AddTail(l.tail, x);
            return l;
        }

        if (c == 3) { // ТУТ ОШИБКА, СДВИГАТЬ
            l.head = AddHead(l.head, x);
            return l;
        }

        if (c == 1) { // если нужно добавить в определенную существующую позицию
            AddAfter(x, p->psPrev);
            return l;
        }
        
        return l;
    }
    
    position lst::locate(object x, position head) {
        position temp = head;
        
        while (temp) {
            if (temp->o == x)
                return temp;
            temp = temp->psNext;
        }
        
        return NULL;
    }
    
    object lst::retrieve(position p, position head) {
        position temp = head;
        
        while (temp) {
            if (temp == p)
                return temp->o;
            temp = temp->psNext;
        }
        
        return F.o; // ненастоящий элемент
    }
    
    pair lst::del(position p, pair l) {
        position n, pr;
        int c = check(p, l.head);
        
        if (p == l.head) {
            l.head = DeleteHead(l.head);
            return l;
        }
        
        if (p == l.tail) {
            l.tail = DeleteTail(l.tail);
            return l;
        }
        
        if (c == 1) {
            n = p->psNext;
            pr = p->psPrev;
            
            pr->psNext = n;
            n->psPrev = pr;
            
            delete p;
        }
        
        return l;
    }
    
    position lst::next(position p, position head) {
        int c = check(p, head);
        
        if (c && c != 2) {
            if (p->psNext)
                return p->psNext;
            else
                return end();
        }
        
        return F.psNext;
    }
    
    position lst::previous(position p, position head) {
        int c = check(p, head);
        
        if (c == 1) {
            if (p->psPrev)
                return p->psPrev;
            else
                return F.psPrev;
        }
        
        return F.psPrev;
    }
    
    position lst::first(position head) {
        if (head)
            return head;
        
        return end();
    }
    
    void lst::print(position head) {
        position temp = head;
        
        while (temp) {
            std::cout << temp->o.name << " " << temp->o.address << std::endl;
            temp = temp->psNext;
        }
    }
    
    position lst::END() {
        return end();
    }
    
    void lst::INSERT(object x, position p) {
        HT = insert(x, p, HT);
    }
    
    position lst::LOCATE(object x) {
        return locate(x, HT.head);
    }
    
    object lst::RETRIEVE(position p) {
        return retrieve(p, HT.head);
    }
    
    void lst::DELETE(position p) {
        HT = del(p, HT);
    }
    
    position lst::NEXT(position p) {
        return next(p, HT.head);
    }
    
    position lst::PREVIOUS(position p) {
        return previous(p, HT.head);
    }
    
    void lst::MAKENULL() {
        HT = ClearList(HT);
    }
    
    position lst::FIRST() {
        return first(HT.head);
    }
    
    void lst::PRINT() {
        print(HT.head);
    }
}

namespace cursor { // курсор
    struct element;
    typedef int position;
    struct element {
        element(object c) : o(c) {}
        element() { o.name[0] = '\0'; o.address[0] = '\0'; next = -2; }
        object o;
        position next;
    };
    
    static const element F;
    
    class lst {
    public:
        lst();
        ~lst();
        int full() const; // проверка полноты
        int empty() const; // проверка пустоты
        position END(); // возвращает следующую позицию после последнего
        void INSERT(object x, position p); // вставить x в позиции p
        position LOCATE(object x); // поиск x в списке, возвращает позицию, если объекта нет, то возв. END();
        object RETRIEVE(position p); // возвращает объект по позиции p, результат неопределен, если p = END();
        void DELETE(position p); // удалить элемент в позиции p
        position NEXT(position p); // следующая позиция после p
        position PREVIOUS(position p); // предыдущая позиция перед p
        position MAKENULL(); // делает список пустым
        position FIRST(); // возвращает первую позицию, если список пуст, то возвращает END();
        void PRINT(); // печать списка
        static void set_a(); // инициализация статического массива
    private:
        position end();
        position insert(object x, position p, position h);
        position locate(object x, position h);
        object retrieve(position p, position h);
        position del(position p, position h);
        position ifExists(position p, position h);
        position next(position p, position h);
        position previous(position p, position h);
        position first(position h);
        void print();
        void transfer(position &a, position &b);
        
        static position space;
        static const int size = 20;
        static element a[size];
        position head;
    };
    
    position lst::space = 0;
    
    void lst::set_a() {
        int i;
        for (i = 0; i < size - 1; i++)
            a[i].next = i;
        a[i].next = -1;
    }
    
    lst::lst() {
        head = end();
    }
    
    lst::~lst() {
        
    }
    
    position lst::end() {
        return -1;
    }
    
    position lst::insert(object x, position p, position h) {
        if (p == F.next) // если пытаемся добавить в несуществующую позицию
            return F.next;
        
        if (p == end()) { // если нужно вставить в конец
            
        }
        
        
    }
    
    position lst::locate(object x, position h) { // вернет позицию искомого объекта. Если такого эл-та в списке нет, то F.next
        while (h > 0) {
            if (x == a[h].o)
                return h;
            else
                h = a[h].next;
        }
        
        return F.next;
    }
    
    object lst::retrieve(position p, position h) {
        while (h > 0) {
            if (p == h)
                return a[h].o;
            else
                h = a[h].next;
        }
        
        return F.o;
    }
    
//    position lst::del(position p, position h) {
//
//    }
    
    position lst::ifExists(position p, position h) { // если элемент есть в списке, то возвращается предыдущий, иначе F.next
        position prev = h;
        
        while (h > 0) {
            if (h == p)
                return prev;
            prev = h;
            h = a[h].next;
        }
        
        return F.next;
    }
    
    position lst::next(position p, position h) {
        if (!empty() && p == h)
            return a[p].next;
        
        position prev = ifExists(p, h);
        
        if (prev != -1)
            return a[p].next;
        
        return F.next;
    }
    
    position lst::previous(position p, position h) {
        if (!empty() && p == h)
            return F.next;
        
        position prev = ifExists(p, h);
        
        if (prev != F.next)
            return prev;
        
        return F.next;
    }
    
    position lst::first(position h) {
        if (h == end())
            return end();
        
        return h;
    }
}

using namespace std;
using namespace list_2connection;

int main() {
    lst L1;
    object x, y;
    strcpy(x.name, "AAA");
    strcpy(x.address, "BBB");
    
    strcpy(y.name, "CCC");
    strcpy(y.address, "DDD");
    
    L1.INSERT(x, L1.END());
    L1.INSERT(y, L1.END());
    
    L1.PRINT();
    
    cout << L1.LOCATE(x) << " " << L1.LOCATE(y) << " " << endl;
    L1.PRINT();
    cout << L1.PREVIOUS(L1.LOCATE(y)) << endl;
    cout << L1.NEXT(L1.LOCATE(x)) << endl;
    
    L1.DELETE(L1.LOCATE(x));
    
    L1.PRINT();
    
    L1.MAKENULL();
    
    L1.PRINT();
}
