#include <stdio.h>

int Prepare(double* array, int capacity);
int SelectData(double* array, int size);
double ComputeResult(double* array, int size);
int Check(double* array, double result, int size);
int iscorrect(int value, int reference);

int main(void)
{
    const int MAX_LEN = 100;

    double resistance[MAX_LEN] = {};
    int real_size = Prepare(resistance, MAX_LEN);

    int new_size = SelectData(resistance, real_size);

    double resistance_final = ComputeResult(resistance, new_size);

    Check(resistance, resistance_final, new_size);

    return 0;
}

int Prepare(double* resistance, int capacity)
{
    double voltage[capacity] = {};
    double amperage[capacity] = {};

    int correct = 0;
    for (; correct < capacity; correct++)
    {
        double volt = 0, ampere = 0;
        if (scanf("%lf %lf", &volt, &ampere) == 2)
        {
            if (ampere != 0 && volt != 0)
            {
                voltage[correct] = volt;
                amperage[correct] = ampere;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            break;
        }
    }

    for (int j = 0; j < correct; j++)
    {
        resistance[j] = voltage[j] / amperage[j];
    }
    return correct;
}

int SelectData(double* array, int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += array[i];
    }

    double array_average = total / size;

    for (int i = 0; i < size; i++)
    {
        if (!iscorrect(array[i], array_average))
        {
            int j = i;
            for (; j < size; j++)
            {
                if (iscorrect(array[j], array_average))
                {
                    break;
                }
            }
            double temp = array[i];
            array[i] = array[j];
            array[j] = temp;

        }

    }
}

double ComputeResult(double* array, int size)
{
}

int Check(double* array, double result, int size)
{
}
