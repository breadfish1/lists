#include <iostream>

struct object {
    char name[30];
    char address[30];
    int operator == (object x) {
       return !strcmp(x.name, name) && !strcmp(x.address, address);
    }
};

namespace arr {
    typedef int position;
    
    struct fake {
        object o;
        fake() { o.name[0] = '\0'; o.address[0] = '\0'; }
    };
    
    static const fake F;
    
    class lst {
    public:
        lst();
        int full() const; // проверка полноты
        int empty() const; // проверка пустоты
        position END(); // возвращает следующую позицию после последнего
        void INSERT(object x, position p); // вставить x в позиции p
        position LOCATE(object x); // поиск x в списке, возвращает позицию, если объекта нет, то возв. END();
        object RETRIEVE(position p); // возвращает объект по позиции p, результат неопределен, если p = END();
        void DELETE(position p); // удалить элемент в позиции p ДОЛЖЕН ЛИ ВОЗВРАЩАТЬ ИНТОВЫЙ UP??
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
        int up;
    };
    
    lst::lst() {
        up = -1;
    }
    
    int lst::empty() const{
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
            s[p] = x; // ГДЕ ТО ПРОБЛЕМА
            up++;
        }
        else {
            std::cout << "There's no space\n";
        }
    }
    
    position lst::locate(object x) {
        for (int i = 0; i < up; i++) // если нашли такой элемент, то возвращаем позицию, иначе -1
            if (x == s[i])
                return i;
        return -1;
    }
    
    object lst::retrieve(position p) {
        if (p > 0 && p <= up)
            return s[p];
        
        return F.o; // НЕ ТАК
    }
    
    void lst::del(position p) {
        if (p <= up) {
            for (int i = p; i < up - 1; i++)
                s[i] = s[i + 1];
            up--;
        }
    }
    
    position lst::next(position p) {
        return up + 1;
    }
    
    position lst::previous(position p) {
        return up - 1;
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

namespace list_1connection {
    struct el {
        el(object c, el *p) : val(c), next(p) {}
        el *next;
        object val;
    };
    
    typedef el *position;
    
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
        el *AddHead(el *h, object x);
        el *ClearList(el *h);
        el *DeleteElement(el *p);
        el *DeleteHead(el *h);
        void AddAfter(object x, el *p);
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
        el *head;
    };
}

list_1connection::lst::lst() {
    head = 0;
}

list_1connection::lst::~lst() {
    el *p = head;
    while (head) {
        head = head->next;
        delete(p);
        p = head;
    }
}

int list_1connection::lst::empty() const {
    return head == 0;
}

int list_1connection::lst::full() const {
    return 0;
}

list_1connection::el *list_1connection::lst::AddHead(list_1connection::el *h, object x) {
    el *q = new el(x, h);
    return q;
}

list_1connection::el *list_1connection::lst::ClearList(list_1connection::el *h) {
    while(h != 0)
        h = DeleteHead(h);

    return NULL;
}

list_1connection::el *list_1connection::lst::DeleteElement(list_1connection::el *p) {
    return NULL;
}

list_1connection::el *list_1connection::lst::DeleteHead(list_1connection::el *h) {
    el *q = h->next;
    delete h;
    return q;
}

void list_1connection::lst::AddAfter(object x, list_1connection::el *p) {
    el *q = new el(x, p->next);
    p->next = q;
}

void list_1connection::lst::print() {
    
}

#include <iostream>
using namespace std;
using namespace arr;

int main() {
    lst L1;
    object x;
    strcpy(x.name, "ASD");
    strcpy(x.address, "George");
    
    L1.INSERT(x, L1.END());
    
    L1.PRINT();
}
