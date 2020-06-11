#ifndef NUTRITIONTRACKER_H
#define NUTRITIONTRACKER_H

#include <QMainWindow>
#include <map>
#include <string>
#include <vector>
#include <QString>
#include <QStringList>


class nutritionTracker : public QMainWindow
{
    Q_OBJECT
public:
    /*Enumerations and Constants*/
    enum class FoodOptions{Meat, Dairy, Carbs, Veg,Other};
    const std::string FOOD_DATA_FILENAME = "data/foodData.csv";
    const int LEN = 11;
private:
    FoodOptions foodTypes;
    struct foodData {
        std::string descrip,
                measurement;
        int cal,
            sodium,
            calcium;
        double carb,
              prot,
              sugar,
              satFat,
              totalFat;
    };
    std::map<FoodOptions,std::vector<foodData>> foodList;
public:
    nutritionTracker();
    QStringList getFoodList (FoodOptions);
    FoodOptions getFoodType ();
    std::vector<foodData> getFoodMapItems(FoodOptions);
    void setFoodType(FoodOptions);
    void readFoodData ();




};

#endif // NUTRITIONTRACKER_H
