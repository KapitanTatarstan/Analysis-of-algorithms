using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AA7_update
{
    class Program
    {
        public static int[,] create_distance_matrix(int cities_number) {
            Random rnd = new Random();
            int[,] matrix = new int[cities_number, cities_number];
            for (int i = 0; i < cities_number; i++)
                for (int j = i + 1; j < cities_number; j++) {
                    //from the minimum distance to the maximum
                    int distance = rnd.Next(1, 10);  
                    // for symmetry of the matrix with respect to the main axis
                    matrix[i, j] = distance;
                    matrix[j, i] = distance;
                }
            return matrix;
        }


        public static void PrintMatrix(int[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                for (int j = 0; j < matrix.GetLength(1); j++)
                    Console.Write("{0,6}", matrix[i, j]);
                Console.WriteLine();
            }
        }

        
        public static void ant_colony_optimization(int[,] distance_matrix,double alpha,double beta,int e,int Q,double p,int cities_number,int time_max, ref int length_route, ref List<int> shortest_route)
        {
            //List<int> shortest_route = new List<int>();
            Random rnd = new Random();
            //int length_route = len;
            int length_to_town = 0;
            int current_town = 0;
            int time = 0;
            double[,] visibility = new double[cities_number,cities_number];
            double[,] pheromons = new double[cities_number, cities_number];

            for (int i = 0; i < cities_number; i++)
                for (int j = 0; j < cities_number; j++)
                {
                    pheromons[i, j] = 0.5;
                    visibility[i, j] = 1 / (distance_matrix[i, j] + 0.001);
                }

            while (time < time_max)
            {
                double[,] for_all_ants = new double[cities_number, cities_number];

                // Для каждого муравья, находящегося в своем городе
                for (int k = 0; k < cities_number; k++)
                {
                    length_to_town = 0; // Дистанция
                    current_town = k;   // Текущий город
                    List<int> ant_town = new List<int>();
                    while (ant_town.Count < cities_number)
                    {
                        List<int> desired_cities = new List<int>();
                        for (int tmp = 0; tmp < cities_number; tmp++)
                            desired_cities.Add(tmp);
                        foreach (var visited_town in ant_town)
                            desired_cities.Remove(visited_town);
                        
                        double[] probability = new double[cities_number]; // Вероятность того, что муравей выберет город
                        foreach(int j in desired_cities)
                        {
                            if (distance_matrix[current_town, j] != 0) // Если путь существует
                            {
                                double temp = 0;
                                foreach (int l in desired_cities)
                                    temp += Math.Pow(pheromons[current_town, l], alpha) * Math.Pow(visibility[current_town, l], beta);
                                probability[desired_cities.IndexOf(j)] = 
                                    Math.Pow(pheromons[current_town,j],alpha) * Math.Pow(visibility[current_town,j],beta) / temp;                               
                            }
                            else
                                probability[desired_cities.IndexOf(j)] = 0;
                        }

                        
                        double max_probability = probability.Max();
                        // Если все пути равны нулю, значит муравей изолирован
                        if (max_probability.Equals(0))
                            break;

                        int selected_city = 0; // Индекс выбранного города
                        // Максимальный ли путь или нет
                        for (int n = 0; n < probability.Length; n++)
                            if (probability[n].Equals(probability.Max()))
                                selected_city = n;


                        ant_town.Add(desired_cities[selected_city]);
                        length_to_town += distance_matrix[current_town,desired_cities[selected_city]];
                        current_town = desired_cities[selected_city];
                        desired_cities.RemoveAt(selected_city);
                    }

              
                    if ((length_route == 0) || ((length_to_town + distance_matrix[ant_town[0], ant_town[ant_town.Count - 1]]) < length_route))
                    {
                        length_route = length_to_town + distance_matrix[ant_town[0], ant_town[ant_town.Count - 1]];
                        shortest_route.Clear();
                        foreach (var item in ant_town)
                            shortest_route.Add(item);
                    }

                    // Обновление феромонов на путях
                    for (int j = 0; j < ant_town.Count - 1; j++)
                    {
                        int a = ant_town[j];
                        int b = ant_town[j + 1];
                        for_all_ants[a, b] += Q / length_to_town;
                    }
                }

                // Обновление

                int for_elite = 0;
                if (length_route != 0)
                    for_elite = (e * Q / length_route);
                else 
                    for_elite = 0;

                
                for (int i = 0; i < cities_number; i++)
                    for (int j = 0; j < cities_number; j++)
                        pheromons[i,j] = (1 - p) * pheromons[i,j] + for_all_ants[i,j] + for_elite;
                time += 1;
                    
            }
            length_route = 0;
            for (int i = 0; i < cities_number-1; i++)
                length_route += distance_matrix[shortest_route[i], shortest_route[i + 1]];
            //len = length_route;
            //return shortest_route;
        }
        
        static void Main(string[] args)
        {
            string str;
            //int len = 0;
            //Console.WriteLine("Введите количество городов");
            //str = Console.ReadLine();
            //int num1 = Convert.ToInt32(str, 10);
            
            //int[,] matrix = new int[num1,num1];
            int[,] matrix = { {0, 3, 9, 6, 6},
                              {3, 0, 1, 7, 4}, 
                              {9, 1, 0, 2, 8}, 
                              {6, 7, 2, 0, 3}, 
                              {6, 4, 8, 3, 0} };
            //matrix = create_distance_matrix(num1);
            //List<int> route = new List<int>();
            PrintMatrix(matrix);

            int cities_count = 5;   // Количество городов
            int time_max = 30;      // Количество поколений
            double alpha = 1;       // Коэффициент усиления влияния феромона
            double beta = 4;        // 
            double p = 0.9;         // Интенсивность испарения
            int e = 5;              // Количество муравьев (изначально)/(скорость распространения)
            int Q = 10;             // Параметр имеющий значение порядка цены оптимального значения
            int len = 0;            // Длина кратчайшего пути
            List<int> route = new List<int>();
            ant_colony_optimization(matrix, alpha, beta, e, Q, p, cities_count, time_max, ref len, ref route);
            Console.WriteLine("Lenght = {0}\n", len);

            
            Console.WriteLine("Путь через вершины:");
            for (int i = 0; i < cities_count; ++i)
            {
                Console.WriteLine(route[i]+1);
            }
            /*
            for (aplha = 0.2, alpha <= 1; alpha += 0.2)
                for (beta = 0; beta < 5; beta += 1)
                    for (p = 0.1, p < 1; p += 0.2) 
                        for (e = 1; e < 5; e += 1)
                            for (time_max = 10; time_max < 35; time_max += 5) {

                    
                            }
            */
            Console.ReadLine();

        }
    }
}
