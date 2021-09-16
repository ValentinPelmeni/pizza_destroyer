#include <iostream>
#include <vector>
#include <string>
#include <string.h>

// Electromagnetic interaction
// You have to create world and be able to add and delete particles from it
// When you add or delete particle you must recalculate all interactions

// Требуется описать мир с некоторыми частицами
// Координата/скорость задается через структуру vector3

struct vector3 {
    double x;
    double y;
    double z;
    vector3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    vector3()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    vector3 operator + (const vector3& other)
    {
        vector3 temp;
        temp.x = this->x + other.x;
        temp.y = this->y + other.y;
        temp.z = this->z + other.z;
        return temp;
    }
    vector3 operator - (const vector3& other)
    {
        vector3 temp;
        temp.x = this->x - other.x;
        temp.y = this->y - other.y;
        temp.z = this->z - other.z;
        return temp;
    }
    double operator * (const vector3& other)
    {
        double temp=0;
        temp += (this->x) * (other.x) + (this->y) * (other.y) + (this->z) * (other.z);
        return temp;
    }

};


std::ostream& operator << (std::ostream& os, const vector3& a)
{
    os << "(" << a.x << " , " << a.y << " , " << a.z << ")" << std::endl;
    return os;
}
// Для описания событий происходящих в мире напишите свой небольшой логгер, который умеет
// Запоминать создание, изменение и уничтожение частиц

class Logger {
public:
    Logger() {};
    void log(const std::string& s) {};
    ~Logger() {};
    void add(std::string Name)
    {
        l.push_back("Added");
        l.push_back(Name);
    }
    void del(std::string Name)
    {
        l.push_back("Deleted");
        l.push_back(Name);
    }
    void edit(std::string Name)
    {
        l.push_back("Edited");
        l.push_back(Name);
    }
private:
    std::vector<std::string> l;
};

// Существует базовый класс частиц, который внутри себя хранит информацию о частице
// Допишите этот родительский класс так, чтобы он мог считать количество объектов, созданных от него

class Particle {
protected:
    // Поля, описывающие частицу
    // Можно дописать свои
    double mass = 0;
    double charge = 0;
    vector3 coordinate = { 0, 0, 0 };
    vector3 velocity = { 0, 0,0 };
    vector3 force = { 0, 0, 0 };
    std::string name;
    // Логгер для записи событий
   

public:
    //static Logger logger;
    Particle() = default;
    explicit Particle(double energy) {};
    // метод, который вам необходимо переопределить в дочерних классах
    // см. или вспомнить лекцию
    // внутри него напишите логику взаимодействия двух частиц (например, кулоновское)
    void interaction(Particle& p1 ,Particle& p2)
    {
        vector3 temp;
        vector3 sub;
        double r = (p1.coordinate - p2.coordinate) * (p1.coordinate - p2.coordinate);
        double force = (p1.charge) * (p2.charge);
        force = force / r;
        force = force / r;
        force = force / r;
        vector3 power(force * p1.coordinate.x, force * p1.coordinate.x, force * p1.coordinate.x);
        p1.force =p1.force + power;

        sub = sub - power;
        p2.force =p2.force+sub;
    };
    void zero()
    {
        vector3 temp;
        this->force = temp;
    }
    std::string getName() const
    {
        return this->name;
    };

};

// описать несколько классов разных частиц
// например такой
class Electron : public Particle {
public:
    int Number=0;
    int chetchik = 0;
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    explicit Electron(vector3 velocity, vector3 coords)
    {
        this->velocity = velocity;
        this->coordinate = coords;
        this->mass = 1;
        this->charge = -1;
        Number++;
        chetchik++;
        this->name="Electron #"+std::to_string(chetchik);
        //logger.add(this->name);

    };
    ~Electron()
    {
        Number--;
        //logger.del(this->name);
    };
};
class Neutron : public Particle {
public:
    int Number = 0;
    int chetchik = 0;
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    explicit Neutron(vector3 velocity, vector3 coords)
    {
        this->velocity = velocity;
        this->coordinate = coords;
        this->mass = 1000000;
        this->charge = 0;
        Number++;
        chetchik++;
        this->name = "Neutron #" + std::to_string(chetchik);
        //logger.add(this->name);

    };
    ~Neutron()
    {
        Number--;
        //logger.del(this->name);
    };
};

// в этом классе опишите мир, состоящий из некоторого числа частиц
class World {
public:
    std::vector<Particle> v;
    // добавить частицу в мир (она должна провзаимодействовать со всеми остальными)
    void addParticle(bool T,vector3 cord,vector3 speed)
    {
        int size = 0;
        if (T) 
        {
            v.push_back(Electron(speed, cord));
            size = v.size();
            if (size > 1)
            {
                for (int i = 0; i < int(v.size()); i++)
                {
                    //v[size].interaction(v[size-1], v[i]);
                }
                ;
            };
        
        }
        else
        {
            v.push_back(Neutron(speed, cord));
            size = v.size();
            if (size != 0)
            {
                for (int i = 0; i < int(v.size()); i++)
                {
                    v[size].interaction(v[size-1], v[i]);
                }
                ;
            };
        }
    };
    // удалить частицу из мира
    void deleteParticle(const Particle& p,int n)
    {
        v.erase(v.begin() + n - 1);
        for (int i = 0; i < int(v.size()); i++)
        {
            v[i].zero();
        };
        for (int i = 0; i < int(v.size()); i++)
        {
            for (int j = 0; j < i; j++)
            {
                v[i].interaction(v[i], v[j]);
            }
        }
    
    
    
    };
};

// перегрузите оператор вывода, чтобы можно было вывести состав мира
// (может потребоваться перегрузка оператора вывода для частиц)
std::ostream& operator<<(std::ostream& os, const World& w)
{
    std::string text = "";
    for (int i = 0; i < int(w.v.size()); i++)
    {
        text = text + w.v[i].getName();
    }
    os << text;
    return os;
};

// здесь создайте мир/миры, куда добавьте некоторое число частиц, взаимодействующих друг с другом
int main()
{
    World world;
    vector3 a(1, 1, 1);
    vector3 b(1, 0, 0);
    world.addParticle(true, a, b);
    world.addParticle(true, b, a);
    std::cout << world;

}