#include <cstdlib>

class Car {

    private:
        float fuel {0.0f};
        float speed {0.0f};
        int passengers {0};
        char *name {};
        int data[5] {1, 2, 3, 4, 5};
        static int totalCnt;
    public:
        Car(void);
        Car(float fuel_initial);
        Car(float fuel_initial, int pass);
        ~Car(void);
        void FillFuel(float fuel_val);
        void Accelerate(void);
        void Brake(void);
        void AddPassengers(int num);
        void Dashboard(void) const;
        static int getTotalCnt(void);
};