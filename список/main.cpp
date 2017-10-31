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
        if (up == -1)
            return end();
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
        position MAKENULL();
        position FIRST();
        void PRINT();
    private:
        int check(position p);
        position AddHead(position h, object x);
        position ClearList(position h);
        position DeleteHead(position h);
        void AddAfter(object x, position p);
        position end();
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
    
    void lst::insert(object x, position p) {
        int c = check(p);
        
        if (!c) // если пользователь пытается добавить в несуществующую позицию
            return;
        
        if (empty()) { // если список пуст, то добавляем в голову
            if (c == 2) // при пустом списке пользователь сможет добавить только в конец, проверяем, что он делает это
                head = AddHead(head, x);
            return;
        }
        
        if (c == 2) { // если нужно добавить в конец, но список не пустой
            position last = head, temp = last;
            while (last) {
                temp = last;
                last = last->ps;
            }
            AddAfter(x, temp);
        }
            
        if (c == 1) // если нужно добавить в определенную существующую позицию
            AddAfter(x, p);
    }
    
    position lst::locate(object x) { // возвращает позицию, если объект найден. если нет, то NULL
        position temp = head;
        
        while (temp) {
            if (temp->o == x)
                return temp;
            temp = temp->ps;
        }
        
        return NULL;
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
        if (check(p)) { //РАБОТАЕТ? ПРОВЕРИТЬ
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
    
    position lst::MAKENULL() {
        return ClearList(head);
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
        position MAKENULL();
        position FIRST();
        void PRINT();
    private:
        int check(position p);
        position AddHead(position h, object x);
        position AddTail(position t, object x);
        position ClearList(position h, position t);
        position DeleteHead(position h);
        position DeleteTail(position t);
        void AddAfter(object x, position p);
        position end();
        void insert(object x, position p);
        position locate(object x);
        object retrieve(position p);
        void del(position p);
        position next(position p);
        position previous(position p);
        position first();
        void print();
        position head, tail;
    };
    
    lst::lst() { ////////////////////////////////////////
        head = NULL;
        tail = NULL;
    }
    
    lst::~lst() { ///////////////////////////////////////
        head = ClearList(head, tail);
        tail = head;
    }
    
    int lst::full() const {
        return head == 0;
    }
    
    int lst::empty() const {
        return 0;
    }
    
    int lst::check(position p) { // возвращает 1, если такой адрес есть в списке, 2, если добавляем в конец, иначе ноль
        position temp = head;
        
        if (p == NULL)
            return 2;
        
        while (temp) {
            if (temp == head)
                return 1;
            temp = temp->psNext;
        }
        
        return 0;
    }
    
    position lst::AddHead(position h, object x) {
        position q = new element(x, h, NULL);
        return q;
    }
    
    position lst::AddTail(position t, object x) {
        position q = new element(x, NULL, t);
        return q;
    }
    
    position lst::ClearList(position h, position t) {
        position p;
        
        while (head) {
            p = head;
            head = head->psNext;
            delete p;
        }
        
        return NULL;
    }
    
    position lst::DeleteHead(position h) {
        position p = head->psNext;
        
        p->psPrev = NULL;
        delete head;
        
        return p;
    }
    
    position lst::DeleteTail(position t) {
        position p = tail->psPrev;
        
        p->psNext = NULL;
        delete tail;
        
        return p;
    }
    
    void lst::AddAfter(object x, position p) {
        position q;
        q->psNext = p->psNext;
        q->psPrev = p;
        p->psNext = q;
        (q->psNext)->psPrev = q;
        q->o = x;
    }
    
    position lst::end() {
        return NULL;
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
        
        if (c == 2) { // если нужно добавить в конец, но список не пустой
            position last = head, temp = last;
            while (last) {
                temp = last;
                last = last->psNext;
            }
            AddAfter(x, temp);
        }
        
        if (c == 1) // если нужно добавить в определенную существующую позицию
            AddAfter(x, p);
    }
    
    position lst::locate(object x) {
        position temp = head;
        
        while (temp) {
            if (temp->o == x)
                return temp;
            temp = temp->psNext;
        }
        
        return NULL;
    }
    
    object lst::retrieve(position p) {
        position temp = head;
        
        while (temp) {
            if (temp == p)
                return temp->o;
            temp = temp->psNext;
        }
        
        return F.o; // ненастоящий элемент
    }
    
    void lst::del(position p) {
        position n, pr;
        
        n = p->psNext;
        pr = p->psPrev;
        
        if (pr)
            pr->psNext = n;
        if (n)
            n->psPrev = pr;
        
        delete p;
    }
    
    position lst::next(position p) {
        if (check(p)) {
            if (p->psNext)
                return p->psNext;
            else
                return end();
        }
        
        return F.psNext;
    }
    
    position lst::previous(position p) {
        if (check(p)) {
            if (p->psPrev)
                return p->psPrev;
            else
                return F.psPrev;
        }
        
        return F.psPrev;
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
            temp = temp->psNext;
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
        del(p);
    }
    
    position lst::NEXT(position p) {
        return next(p);
    }
    
    position lst::PREVIOUS(position p) {
        return previous(p);
    }
    
    position lst::MAKENULL() {
        return ClearList(head, tail);
    }
    
    position lst::FIRST() {
        return first();
    }
    
    void lst::PRINT() {
        print();
    }
}


#include <iostream>
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
}
