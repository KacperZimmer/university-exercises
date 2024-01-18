//Kacper Zimmer
#include <iostream>
using namespace std;

#define SET_AP 0
#define SET_AS 1
#define SET_AR 2
#define SET_AW 3
#define SET_HW 4
#define SET_HR 5
#define SET_HS 6

#define PUT_W 7
#define PUT_H 8
#define PUT_R 9
#define PUT_S 10

#define FILL 11

#define POP_W 12
#define POP_H 13
#define POP_R 14
#define POP_S 15

#define MOV_W 16
#define MOV_H 17
#define MOV_R 18
#define MOV_S 19

#define GET_E 20
#define GET_W 21
#define GET_RW 22
#define GET_RH 23
#define GET_SW 24
#define GET_SH 25
#define GET_SR 26
#define GET_S 27

#define SET_LW 28
#define SET_LH 29
#define SET_LR 30
#define SET_LS 31

#define GET_LW 32
#define GET_LH 33
#define GET_LR 34
#define GET_LS 35

#define END 100
#define UNDEFINED_COMMAND 101

const int places_quantity = 128;
const int shelves_quantity = 128;
const int racks_quantity = 128;
const int warehouses_quantity = 128;
const int max_place_stuff_quantity = 65535;

unsigned long long total_storehouse_stuff = 0;

struct Place
{
    unsigned short int stuff = 0;
    char label[2] = { 0 , 0 };
};

struct Shelf
{
    unsigned short int places_number = 0;
    Place places[places_quantity];
};

struct Rack
{
    unsigned short int shelves_number = 0;
    Shelf shelves[shelves_quantity];
};

struct Warehouse
{
    unsigned short int racks_number = 0;
    Rack racks[racks_quantity];
    Shelf handy_shelf;
};

struct Storehouse
{
    unsigned short int warehouses_number = 0;
    Warehouse warehouses[warehouses_quantity];
    Rack handy_rack;
    Shelf handy_shelf;
}main_storehouse;


int get_string_length(const char* string)
{
    int length = 0;

    for (int index = 0; string[index] != '\0'; index++)
    {
        length++;
    }

    return length;
}

bool compare_strings(char* string1, const char* string2)
{
    bool strings_equal = true;

    if (get_string_length(string1) == get_string_length(string2))
    {
        for (int index = 0; string1[index] != '\0'; index++)
        {
            if (string1[index] != string2[index])
            {
                strings_equal = false;
                break;
            }
        }
    }
    else
        strings_equal = false;

    return strings_equal;
}

int decode_command(char command_to_decode[])
{
    if (compare_strings(command_to_decode, "SET-AP"))
        return SET_AP;
    else if (compare_strings(command_to_decode, "SET-AS"))
        return SET_AS;
    else if (compare_strings(command_to_decode, "SET-AE"))
        return SET_AR;
    else if (compare_strings(command_to_decode, "SET-AW"))
        return SET_AW;
    else if (compare_strings(command_to_decode, "SET-HW"))
        return SET_HW;
    else if (compare_strings(command_to_decode, "SET-HR"))
        return SET_HR;
    else if (compare_strings(command_to_decode, "SET-HS"))
        return SET_HS;
    else if (compare_strings(command_to_decode, "PUT-W"))
        return PUT_W;
    else if (compare_strings(command_to_decode, "PUT-H"))
        return PUT_H;
    else if (compare_strings(command_to_decode, "PUT-R"))
        return PUT_R;
    else if (compare_strings(command_to_decode, "PUT-S"))
        return PUT_S;
    else if (compare_strings(command_to_decode, "FILL"))
        return FILL;
    else if (compare_strings(command_to_decode, "POP-W"))
        return POP_W;
    else if (compare_strings(command_to_decode, "POP-H"))
        return POP_H;
    else if (compare_strings(command_to_decode, "POP-R"))
        return POP_R;
    else if (compare_strings(command_to_decode, "POP-S"))
        return POP_S;
    else if (compare_strings(command_to_decode, "MOV-W"))
        return MOV_W;
    else if (compare_strings(command_to_decode, "MOV-H"))
        return MOV_H;
    else if (compare_strings(command_to_decode, "MOV-R"))
        return MOV_R;
    else if (compare_strings(command_to_decode, "MOV-S"))
        return MOV_S;
    else if (compare_strings(command_to_decode, "GET-E"))
        return GET_E;
    else if (compare_strings(command_to_decode, "GET-W"))
        return GET_W;
    else if (compare_strings(command_to_decode, "GET-RW"))
        return GET_RW;
    else if (compare_strings(command_to_decode, "GET-RH"))
        return GET_RH;
    else if (compare_strings(command_to_decode, "GET-SW"))
        return GET_SW;
    else if (compare_strings(command_to_decode, "GET-SH"))
        return GET_SH;
    else if (compare_strings(command_to_decode, "GET-SR"))
        return GET_SR;
    else if (compare_strings(command_to_decode, "GET-S"))
        return GET_S;
    else if (compare_strings(command_to_decode, "SET-LW"))
        return SET_LW;
    else if (compare_strings(command_to_decode, "SET-LH"))
        return SET_LH;
    else if (compare_strings(command_to_decode, "SET-LR"))
        return SET_LR;
    else if (compare_strings(command_to_decode, "SET-LS"))
        return SET_LS;
    else if (compare_strings(command_to_decode, "GET-LW"))
        return GET_LW;
    else if (compare_strings(command_to_decode, "GET-LH"))
        return GET_LH;
    else if (compare_strings(command_to_decode, "GET-LR"))
        return GET_LR;
    else if (compare_strings(command_to_decode, "GET-LS"))
        return GET_LS;
    else if (compare_strings(command_to_decode, "END"))
        return END;
    else
        return UNDEFINED_COMMAND;
}

void print_error()
{
    cout << "error" << endl;
}

bool check_warehouses_count(unsigned short int warehouse_number)
{
    if (main_storehouse.warehouses_number > warehouse_number)
        return true;
    else
        return false;
}

bool check_racks_count(unsigned short int rack_number, unsigned short int warehouse_number)
{
    if (check_warehouses_count(warehouse_number) && main_storehouse.warehouses[warehouse_number].racks_number > rack_number)
    {
        return true;
    }
    else
        return false;
}

bool check_shelves_count(unsigned short int shelf_number, unsigned short int rack_number, unsigned short int warehouse_number)
{
    if (check_racks_count(rack_number, warehouse_number) && main_storehouse.warehouses[warehouse_number].racks[rack_number].shelves_number > shelf_number)
    {
        return true;
    }
    else
        return false;
}

bool check_places_count(unsigned short int place_number, unsigned short int shelf_number, unsigned short int rack_number, unsigned short int warehouse_number)
{
    if (check_shelves_count(shelf_number, rack_number, warehouse_number) && main_storehouse.warehouses[warehouse_number].racks[rack_number].shelves[shelf_number].places_number > place_number)
    {
        return true;
    }
    else
        return false;
}

void zero_places(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned short int places_count)
{
    for (int element_to_zero = p; element_to_zero < places_count; element_to_zero++)
    {
        total_storehouse_stuff -= main_storehouse.warehouses[w].racks[r].shelves[s].places[element_to_zero].stuff;
        main_storehouse.warehouses[w].racks[r].shelves[s].places[element_to_zero].stuff = 0;
        main_storehouse.warehouses[w].racks[r].shelves[s].places[element_to_zero].label[0] = 0;
        main_storehouse.warehouses[w].racks[r].shelves[s].places[element_to_zero].label[1] = 0;
    }
}

void zero_shelves(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned short int shelves_count)
{
    for (int element_to_zero = s; element_to_zero < shelves_count; element_to_zero++)
    {
        zero_places(w, r, element_to_zero, p, main_storehouse.warehouses[w].racks[r].shelves[element_to_zero].places_number);
    }
}

void zero_handy_shelf(unsigned short int warehouse_number, unsigned int places_start, unsigned int places_end)
{
    for (int handy_shelf_places = places_start; handy_shelf_places < places_end; handy_shelf_places++)
    {
        total_storehouse_stuff -= main_storehouse.warehouses[warehouse_number].handy_shelf.places[handy_shelf_places].stuff;
        main_storehouse.warehouses[warehouse_number].handy_shelf.places[handy_shelf_places].stuff = 0;
        main_storehouse.warehouses[warehouse_number].handy_shelf.places[handy_shelf_places].label[0] = 0;
        main_storehouse.warehouses[warehouse_number].handy_shelf.places[handy_shelf_places].label[1] = 0;
    }
}

void zero_handy_storehouse_shelf(unsigned int places_start, unsigned int places_end)
{
    for (int handy_shelf_places = places_start; handy_shelf_places < places_end; handy_shelf_places++)
    {
        total_storehouse_stuff -= main_storehouse.handy_shelf.places[handy_shelf_places].stuff;
        main_storehouse.handy_shelf.places[handy_shelf_places].stuff = 0;
        main_storehouse.handy_shelf.places[handy_shelf_places].label[0] = 0;
        main_storehouse.handy_shelf.places[handy_shelf_places].label[1] = 0;
    }
}

void zero_racks(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned short int racks_count)
{
    for (int element_to_zero = r; element_to_zero < racks_count; element_to_zero++)
    {
        zero_shelves(w, element_to_zero, s, p, main_storehouse.warehouses[w].racks[element_to_zero].shelves_number);
    }
}

void zero_handy_rack(unsigned int shelves_start, unsigned int shelves_end)
{
    for (int handy_rack_shelves = shelves_start; handy_rack_shelves < shelves_end; handy_rack_shelves++)
    {
        for (int place_element = 0; place_element < main_storehouse.handy_rack.shelves[handy_rack_shelves].places_number; place_element++)
        {
            total_storehouse_stuff -= main_storehouse.handy_rack.shelves[handy_rack_shelves].places[place_element].stuff;
            main_storehouse.handy_rack.shelves[handy_rack_shelves].places[place_element].stuff = 0;
            main_storehouse.handy_rack.shelves[handy_rack_shelves].places[place_element].label[0] = 0;
            main_storehouse.handy_rack.shelves[handy_rack_shelves].places[place_element].label[1] = 0;

        }
    }
}

void zero_warehouses(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned short int warehouse_count)
{
    for (int element_to_zero = w; element_to_zero < warehouse_count; element_to_zero++)
    {
        zero_racks(element_to_zero, r, s, p, main_storehouse.warehouses[element_to_zero].racks_number);
        zero_handy_shelf(element_to_zero, 0, main_storehouse.warehouses[element_to_zero].handy_shelf.places_number);
    }
}

bool set_ap(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p)
{
    if (check_shelves_count(s, r, w))
    {
        int previous_places = main_storehouse.warehouses[w].racks[r].shelves[s].places_number;

        zero_places(w, r, s, p, previous_places);

        main_storehouse.warehouses[w].racks[r].shelves[s].places_number = p;
    }
    else
        return false;

    return true;
}

bool set_as(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p)
{
    if (check_racks_count(r, w))
    {
        int previous_shelves = main_storehouse.warehouses[w].racks[r].shelves_number;

        zero_shelves(w, r, s, p, previous_shelves);

        main_storehouse.warehouses[w].racks[r].shelves_number = s;

        for (int element_to_set = 0; element_to_set < s; element_to_set++)
        {
            if (set_ap(w, r, s, p) == false)
                return false;
        }
    }
    else
        return false;

    return true;
}

bool set_ar(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p)
{
    if (check_warehouses_count(w))
    {
        int previous_racks = main_storehouse.warehouses[w].racks_number;

        zero_racks(w, r, s, p, previous_racks);

        main_storehouse.warehouses[w].racks_number = r;

        for (int element_to_set = 0; element_to_set < r; element_to_set++)
        {
            if (set_as(w, r, s, p) == false)
                return false;
        }

    }
    else
        return false;

    return true;
}

bool set_aw(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p)
{

    int previous_warrehouses = main_storehouse.warehouses_number;

    zero_warehouses(w, r, s, p, previous_warrehouses);

    main_storehouse.warehouses_number = w;

    for (int element_to_set = 0; element_to_set < w; element_to_set++)
    {
        if (set_ar(w, r, s, p) == false)
            return false;
    }

    return true;
}

bool set_hw(unsigned short int w, unsigned short int p)
{
    if (check_warehouses_count(w))
    {
        zero_handy_shelf(w, p, main_storehouse.warehouses[w].handy_shelf.places_number);
        main_storehouse.warehouses[w].handy_shelf.places_number = p;
    }
    else
        return false;

    return true;
}

void set_hr(unsigned short int s, unsigned short int p)
{
    zero_handy_rack(s, main_storehouse.handy_rack.shelves_number);
    main_storehouse.handy_rack.shelves_number = s;

    for (int shelf_element = 0; shelf_element < s; shelf_element++)
    {
        int previous_places = main_storehouse.handy_rack.shelves[0].places_number;

        for (int element_to_zero = p; element_to_zero < previous_places; element_to_zero++)
        {
            total_storehouse_stuff -= main_storehouse.handy_rack.shelves[shelf_element].places[element_to_zero].stuff;
            main_storehouse.handy_rack.shelves[shelf_element].places[element_to_zero].stuff = 0;
            main_storehouse.handy_rack.shelves[shelf_element].places[element_to_zero].label[0] = 0;
            main_storehouse.handy_rack.shelves[shelf_element].places[element_to_zero].label[1] = 0;
        }

        main_storehouse.handy_rack.shelves[shelf_element].places_number = p;
    }
}

void set_hs(unsigned short int p)
{
    zero_handy_storehouse_shelf(p, main_storehouse.handy_shelf.places_number);
    main_storehouse.handy_shelf.places_number = p;
}

bool put_w(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned int a)
{
    if (check_places_count(p, s, r, w))
    {
        if ((main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff + a) > max_place_stuff_quantity)
        {
            total_storehouse_stuff += max_place_stuff_quantity - main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff;
            main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff = max_place_stuff_quantity;
        }
        else
        {
            total_storehouse_stuff += a;
            main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff += a;
        }
    }
    else
        return false;

    return true;
}

bool put_h(unsigned short int w, unsigned short int p, unsigned int a)
{
    if (check_warehouses_count(w) && (main_storehouse.warehouses[w].handy_shelf.places_number >= p))
    {
        if ((main_storehouse.warehouses[w].handy_shelf.places[p].stuff + a) > max_place_stuff_quantity)
        {
            total_storehouse_stuff += max_place_stuff_quantity - main_storehouse.warehouses[w].handy_shelf.places[p].stuff;
            main_storehouse.warehouses[w].handy_shelf.places[p].stuff = max_place_stuff_quantity;
        }
        else
        {
            total_storehouse_stuff += a;
            main_storehouse.warehouses[w].handy_shelf.places[p].stuff += a;
        }
    }
    else
        return false;

    return true;
}

bool put_r(unsigned short int s, unsigned short int p, unsigned int a)
{
    if (main_storehouse.handy_rack.shelves_number >= s)
    {
        if ((main_storehouse.handy_rack.shelves[s].places_number >= p))
        {
            if ((main_storehouse.handy_rack.shelves[s].places[p].stuff + a) > max_place_stuff_quantity)
            {
                total_storehouse_stuff += max_place_stuff_quantity - main_storehouse.handy_rack.shelves[s].places[p].stuff;
                main_storehouse.handy_rack.shelves[s].places[p].stuff = max_place_stuff_quantity;
            }
            else
            {
                total_storehouse_stuff += a;
                main_storehouse.handy_rack.shelves[s].places[p].stuff += a;
            }
        }
        else
            return false;
    }
    else
        return false;

    return true;
}

bool put_s(unsigned short int p, unsigned int a)
{
    if (main_storehouse.handy_shelf.places_number >= p)
    {
        if ((main_storehouse.handy_shelf.places[p].stuff + a) > max_place_stuff_quantity)
        {
            total_storehouse_stuff += max_place_stuff_quantity - main_storehouse.handy_shelf.places[p].stuff;
            main_storehouse.handy_shelf.places[p].stuff = max_place_stuff_quantity;
        }
        else
        {
            total_storehouse_stuff += a;
            main_storehouse.handy_shelf.places[p].stuff += a;
        }
    }
    else
        return false;

    return true;
}

void fill(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned int a)
{
    zero_handy_rack(0, main_storehouse.handy_rack.shelves_number);
    zero_handy_storehouse_shelf(0, main_storehouse.handy_shelf.places_number);
    zero_warehouses(0, 0, 0, 0, main_storehouse.warehouses_number);

    int stuff_quantity_to_set = a;
    if (a > 65535)
        stuff_quantity_to_set = 65535;

    main_storehouse.warehouses_number = w;
    main_storehouse.handy_rack.shelves_number = s;
    main_storehouse.handy_shelf.places_number = p;

    for (int warehouse = 0; warehouse < main_storehouse.warehouses_number; warehouse++)
    {
        main_storehouse.warehouses[warehouse].handy_shelf.places_number = p;
        main_storehouse.warehouses[warehouse].racks_number = r;

        for (int rack = 0; rack < main_storehouse.warehouses[warehouse].racks_number; rack++)
        {
            main_storehouse.warehouses[warehouse].racks[rack].shelves_number = s;

            for (int shelf = 0; shelf < main_storehouse.warehouses[warehouse].racks[rack].shelves_number; shelf++)
            {
                main_storehouse.warehouses[warehouse].racks[rack].shelves[shelf].places_number = p;

                for (int place = 0; place < main_storehouse.warehouses[warehouse].racks[rack].shelves[shelf].places_number; place++)
                {
                    total_storehouse_stuff += stuff_quantity_to_set;
                    main_storehouse.warehouses[warehouse].racks[rack].shelves[shelf].places[place].stuff = stuff_quantity_to_set;
                    main_storehouse.warehouses[warehouse].racks[rack].shelves[shelf].places[place].label[0] = 0;
                    main_storehouse.warehouses[warehouse].racks[rack].shelves[shelf].places[place].label[1] = 0;
                }
            }
        }

        for (int handy_place = 0; handy_place < main_storehouse.warehouses[warehouse].handy_shelf.places_number; handy_place++)
        {
            total_storehouse_stuff += stuff_quantity_to_set;
            main_storehouse.warehouses[warehouse].handy_shelf.places[handy_place].stuff = stuff_quantity_to_set;
            main_storehouse.warehouses[warehouse].handy_shelf.places[handy_place].label[0] = 0;
            main_storehouse.warehouses[warehouse].handy_shelf.places[handy_place].label[1] = 0;
        }
    }

    for (int handy_shelf = 0; handy_shelf < main_storehouse.handy_rack.shelves_number; handy_shelf++)
    {
        main_storehouse.handy_rack.shelves[handy_shelf].places_number = p;

        for (int handy_place = 0; handy_place < main_storehouse.handy_rack.shelves[handy_shelf].places_number; handy_place++)
        {
            total_storehouse_stuff += stuff_quantity_to_set;
            main_storehouse.handy_rack.shelves[handy_shelf].places[handy_place].stuff = stuff_quantity_to_set;
            main_storehouse.handy_rack.shelves[handy_shelf].places[handy_place].label[0] = 0;
            main_storehouse.handy_rack.shelves[handy_shelf].places[handy_place].label[1] = 0;
        }
    }

    for (int handy_place = 0; handy_place < main_storehouse.handy_shelf.places_number; handy_place++)
    {
        total_storehouse_stuff += stuff_quantity_to_set;
        main_storehouse.handy_shelf.places[handy_place].stuff = stuff_quantity_to_set;
        main_storehouse.handy_shelf.places[handy_place].label[0] = 0;
        main_storehouse.handy_shelf.places[handy_place].label[1] = 0;
    }

}

bool pop_w(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned int a)
{
    if (check_places_count(p, s, r, w))
    {
        int difference = main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff - a;
        if (difference < 0)
        {
            total_storehouse_stuff -= main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff;
            main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff = 0;
        }
        else
        {
            total_storehouse_stuff -= a;
            main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff -= a;
        }
    }
    else
        return false;

    return true;
}





bool pop_s(unsigned short int p, unsigned int a)
{
    if (main_storehouse.handy_shelf.places_number >= p)
    {
        int difference = main_storehouse.handy_shelf.places[p].stuff - a;
        if (difference < 0)
        {
            total_storehouse_stuff -= main_storehouse.handy_shelf.places[p].stuff;
            main_storehouse.handy_shelf.places[p].stuff = 0;
        }
        else
        {
            total_storehouse_stuff -= a;
            main_storehouse.handy_shelf.places[p].stuff -= a;
        }
    }
    else
        return false;

    return true;
}

bool mov_w(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int w1, unsigned short int r1, unsigned short int s1, unsigned short int p, unsigned short int a)
{
    if (check_places_count(p, s, r, w) && check_places_count(p, r1, s1, w1))
    {
        int quantity_to_move = 0;
        int stuff_to_move = main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff;
        int stuff_take = main_storehouse.warehouses[w1].racks[r1].shelves[s1].places[p].stuff;

        if (stuff_to_move < a)
            quantity_to_move = stuff_to_move;
        else
            quantity_to_move = a;

        if ((stuff_take + quantity_to_move) > max_place_stuff_quantity)
            quantity_to_move = max_place_stuff_quantity - stuff_take;

        pop_w(w, r, s, p, quantity_to_move);
        put_w(w1, r1, s1, p, quantity_to_move);

    }
    else
        return false;

    return true;
}

bool mov_h(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned short int a)
{
    if (check_places_count(p, s, r, w))
    {
        if (main_storehouse.warehouses[w].handy_shelf.places_number >= p)
        {

            int quantity_to_move = 0;
            int stuff_to_move = main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff;
            int stuff_take = main_storehouse.warehouses[w].handy_shelf.places[p].stuff;

            if (stuff_to_move < a)
                quantity_to_move = stuff_to_move;
            else
                quantity_to_move = a;

            if ((stuff_take + quantity_to_move) > max_place_stuff_quantity)
                quantity_to_move = max_place_stuff_quantity - stuff_take;

            pop_w(w, r, s, p, quantity_to_move);
            put_h(w, p, quantity_to_move);
        }
        else
            return false;
    }
    else
        return false;

    return true;
}

bool mov_r(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int s1, unsigned short int p, unsigned short int a)
{
    if (check_places_count(p, s, r, w))
    {
        if (main_storehouse.handy_rack.shelves_number >= s1)
        {
            if ((main_storehouse.handy_rack.shelves[s1].places_number >= p))
            {
                int quantity_to_move = 0;
                int stuff_to_move = main_storehouse.warehouses[w].racks[r].shelves[s].places[p].stuff;
                int stuff_take = main_storehouse.handy_rack.shelves[s1].places[p].stuff;

                if (stuff_to_move < a)
                    quantity_to_move = stuff_to_move;
                else
                    quantity_to_move = a;

                if ((stuff_take + quantity_to_move) > max_place_stuff_quantity)
                    quantity_to_move = max_place_stuff_quantity - stuff_take;

                pop_w(w, r, s, p, quantity_to_move);
                put_r(s1, p, quantity_to_move);
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;

    return true;
}



void get_e()
{
    cout << total_storehouse_stuff << endl;
}

bool get_w(unsigned short int w)
{
    if (check_warehouses_count(w))
    {
        unsigned long long int total_warehouse_stuff = 0;

        for (int actual_rack = 0; actual_rack < main_storehouse.warehouses[w].racks_number; actual_rack++)
        {
            for (int actual_shelf = 0; actual_shelf < main_storehouse.warehouses[w].racks[actual_rack].shelves_number; actual_shelf++)
            {
                for (int actual_place = 0; actual_place < main_storehouse.warehouses[w].racks[actual_rack].shelves[actual_shelf].places_number; actual_place++)
                {
                    total_warehouse_stuff += main_storehouse.warehouses[w].racks[actual_rack].shelves[actual_shelf].places[actual_place].stuff;
                }
            }
        }

        for (int actual_handy_place = 0; actual_handy_place < main_storehouse.warehouses[w].handy_shelf.places_number; actual_handy_place++)
        {
            total_warehouse_stuff += main_storehouse.warehouses[w].handy_shelf.places[actual_handy_place].stuff;
        }

        cout << total_warehouse_stuff << endl;
        return true;
    }
    else
        return false;

}

bool get_rw(unsigned short int w, unsigned short int r)
{
    if (check_racks_count(r, w))
    {
        unsigned long long int total_rack_stuff = 0;

        for (int actual_shelf = 0; actual_shelf < main_storehouse.warehouses[w].racks[r].shelves_number; actual_shelf++)
        {
            for (int actual_place = 0; actual_place < main_storehouse.warehouses[w].racks[r].shelves[actual_shelf].places_number; actual_place++)
            {
                total_rack_stuff += main_storehouse.warehouses[w].racks[r].shelves[actual_shelf].places[actual_place].stuff;
            }
        }

        cout << total_rack_stuff << endl;
        return true;
    }
    else
        return false;

}

void get_rh()
{
    unsigned long long int total_rack_stuff = 0;

    for (int actual_shelf = 0; actual_shelf < main_storehouse.handy_rack.shelves_number; actual_shelf++)
    {
        for (int actual_place = 0; actual_place < main_storehouse.handy_rack.shelves[actual_shelf].places_number; actual_place++)
        {
            total_rack_stuff += main_storehouse.handy_rack.shelves[actual_shelf].places[actual_place].stuff;
        }
    }

    cout << total_rack_stuff << endl;
}

bool get_sw(unsigned short int w, unsigned short int r, unsigned short int s)
{
    if (check_shelves_count(s, r, w))
    {
        unsigned long long int total_shelf_stuff = 0;

        for (int actual_place = 0; actual_place < main_storehouse.warehouses[w].racks[r].shelves[s].places_number; actual_place++)
        {
            total_shelf_stuff += main_storehouse.warehouses[w].racks[r].shelves[s].places[actual_place].stuff;
        }

        cout << total_shelf_stuff << endl;
        return true;
    }
    else
        return false;
}

bool get_sh(unsigned short int w)
{
    if (check_warehouses_count(w))
    {
        unsigned long long int total_shelf_stuff = 0;

        for (int actual_handy_place = 0; actual_handy_place < main_storehouse.warehouses[w].handy_shelf.places_number; actual_handy_place++)
        {
            total_shelf_stuff += main_storehouse.warehouses[w].handy_shelf.places[actual_handy_place].stuff;
        }

        cout << total_shelf_stuff << endl;
        return true;
    }
    else
        return false;
}

bool get_sr(unsigned short int s)
{
    unsigned long long int total_shelf_stuff = 0;

    if (main_storehouse.handy_rack.shelves_number >= s)
    {
        for (int actual_place = 0; actual_place < main_storehouse.handy_rack.shelves[s].places_number; actual_place++)
        {
            total_shelf_stuff += main_storehouse.handy_rack.shelves[s].places[actual_place].stuff;
        }

        cout << total_shelf_stuff << endl;
        return true;
    }
    else
        return false;
}

void get_s()
{
    unsigned long long int total_shelf_stuff = 0;

    for (int actual_place = 0; actual_place < main_storehouse.handy_shelf.places_number; actual_place++)
    {
        total_shelf_stuff += main_storehouse.handy_shelf.places[actual_place].stuff;
    }

    cout << total_shelf_stuff << endl;
}

bool set_lw(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned char dd[])
{
    if (check_places_count(p, s, r, w))
    {
        main_storehouse.warehouses[w].racks[r].shelves[s].places[p].label[0] = dd[0];
        main_storehouse.warehouses[w].racks[r].shelves[s].places[p].label[1] = dd[1];

        return true;
    }
    else
        return false;
}

bool set_lh(unsigned short int w, unsigned short int p, unsigned char dd[])
{
    if (check_warehouses_count(w))
    {
        if (main_storehouse.warehouses[w].handy_shelf.places_number >= p)
        {
            main_storehouse.warehouses[w].handy_shelf.places[p].label[0] = dd[0];
            main_storehouse.warehouses[w].handy_shelf.places[p].label[1] = dd[1];
        }
        else
            return false;
    }
    else
        return false;

    return true;
}

bool set_lr(unsigned short int s, unsigned short int p, unsigned char dd[])
{
    if (main_storehouse.handy_rack.shelves_number >= s)
    {
        if (main_storehouse.handy_rack.shelves[s].places_number >= p)
        {
            main_storehouse.handy_rack.shelves[s].places[p].label[0] = dd[0];
            main_storehouse.handy_rack.shelves[s].places[p].label[1] = dd[1];
        }
        else
            return false;
    }
    else
        return false;

    return true;
}

bool set_ls(unsigned short int p, unsigned char dd[])
{
    if (main_storehouse.handy_shelf.places_number >= p)
    {
        main_storehouse.handy_shelf.places[p].label[0] = dd[0];
        main_storehouse.handy_shelf.places[p].label[1] = dd[1];
    }
    else
        return false;

    return true;
}





const int command_size = 6;

int main()
{
    bool run_loop = true;
    char command[command_size];

    unsigned int w, r, s, p, a, w1, r1, s1;
    unsigned char dd[2] = { '0', '0' };

    do
    {
        cin >> command;

        switch (decode_command(command))
        {
            case SET_AP:
            {
                cin >> w >> r >> s >> p;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_ap(w, r, s, p) == false)
                        print_error();
                }
                break;
            }
            case SET_AS:
            {
                cin >> w >> r >> s >> p;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_as(w, r, s, p) == false)
                        print_error();
                }
                break;
            }
            case SET_AR:
            {
                cin >> w >> r >> s >> p;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_ar(w, r, s, p) == false)
                        print_error();
                }
                break;
            }
            case SET_AW:
            {
                cin >> w >> r >> s >> p;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_aw(w, r, s, p) == false)
                        print_error();
                }
                break;
            }
            case SET_HW:
            {
                cin >> w >> p;

                if ((w >= warehouses_quantity || w < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_hw(w, p) == false)
                        print_error();
                }
                break;
            }
            case SET_HR:
            {
                cin >> s >> p;

                if ((s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                    set_hr(s, p);

                break;
            }
            case SET_HS:
            {
                cin >> p;

                if (p >= places_quantity || p < 0)
                    print_error();
                else
                    set_hs(p);

                break;
            }
            case PUT_W:
            {
                cin >> w >> r >> s >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (put_w(w, r, s, p, a) == false)
                        print_error();
                }
                break;
            }
            case PUT_H:
            {
                cin >> w >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (put_h(w, p, a) == false)
                        print_error();
                }
                break;
            }
            case PUT_R:
            {
                cin >> s >> p >> a;

                if ((s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (put_r(s, p, a) == false)
                        print_error();
                }
                break;
            }
            case PUT_S:
            {
                cin >> p >> a;

                if ((p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (put_s(p, a) == false)
                        print_error();
                }
                break;
            }
            case FILL:
            {
                cin >> w >> r >> s >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    fill(w, r, s, p, a);
                }
                break;
            }
            case POP_W:
            {
                cin >> w >> r >> s >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (pop_w(w, r, s, p, a) == false)
                        print_error();
                }
                break;
            }
            case POP_H:
            {
                cin >> w >> p >> a;


                print_error();
                break;
            }
            case POP_R:
            {
                cin >> s >> p >> a;

                    print_error();

                break;
            }
            case POP_S:
            {
                cin >> p >> a;

                if ((p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (pop_s(p, a) == false)
                        print_error();
                }
                break;
            }
            case MOV_W:
            {
                cin >> w >> r >> s >> w1 >> r1 >> s1 >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) ||
                    (w1 >= warehouses_quantity || w1 < 0) || (r1 >= racks_quantity || r1 < 0) || (s1 >= shelves_quantity || s1 < 0) ||
                    (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (mov_w(w, r, s, w1, r1, s1, p, a) == false)
                        print_error();
                }
                break;
            }
            case MOV_H:
            {
                cin >> w >> r >> s >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (mov_h(w, r, s, p, a) == false)
                        print_error();
                }
                break;
            }
            case MOV_R:
            {
                cin >> w >> r >> s >> s1 >> p >> a;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (s1 >= shelves_quantity || s1 < 0) || (p >= places_quantity || p < 0) || a < 0)
                    print_error();
                else
                {
                    if (mov_r(w, r, s, s1, p, a) == false)
                        print_error();
                }
                break;
            }
            case MOV_S:
            {
                cin >> s >> p >> a;



                print_error();

                break;
            }
            case GET_E:
            {
                get_e();
                break;
            }
            case GET_W:
            {
                cin >> w;

                if (w >= warehouses_quantity || w < 0)
                    print_error();
                else
                {
                    if (get_w(w) == false)
                        print_error();
                }
                break;
            }
            case GET_RW:
            {
                cin >> w >> r;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0))
                    print_error();
                else
                {
                    if (get_rw(w, r) == false)
                        print_error();
                }
                break;
            }
            case GET_RH:
            {
                get_rh();
                break;
            }
            case GET_SW:
            {
                cin >> w >> r >> s;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0))
                    print_error();
                else
                {
                    if (get_sw(w, r, s) == false)
                        print_error();
                }
                break;
            }
            case GET_SH:
            {
                cin >> w;
                if (w >= warehouses_quantity || w < 0)
                    print_error();
                else
                {
                    if (get_sh(w) == false)
                        print_error();
                }
                break;
            }
            case GET_SR:
            {
                cin >> s;
                if (s >= shelves_quantity || s < 0)
                    print_error();
                else
                {
                    if (get_sr(s) == false)
                        print_error();
                }
                break;
            }
            case GET_S:
            {
                get_s();

                break;
            }
            case SET_LW:
            {
                cin >> w >> r >> s >> p >> dd;

                if ((w >= warehouses_quantity || w < 0) || (r >= racks_quantity || r < 0) || (s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_lw(w, r, s, p, dd) == false)
                        print_error();
                }
                break;
            }
            case SET_LH:
            {
                cin >> w >> p >> dd;

                if ((w >= warehouses_quantity || w < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_lh(w, p, dd) == false)
                        print_error();
                }
                break;
            }
            case SET_LR:
            {
                cin >> s >> p >> dd;

                if ((s >= shelves_quantity || s < 0) || (p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_lr(s, p, dd) == false)
                        print_error();
                }
                break;
            }
            case SET_LS:
            {
                cin >> p >> dd;

                if ((p >= places_quantity || p < 0))
                    print_error();
                else
                {
                    if (set_ls(p, dd) == false)
                        print_error();
                }
                break;
            }
            case GET_LW:
            {
                cin >> w >> r >> s >> p;

                    print_error();
                        print_error();
            }
            case GET_LH:
            {
                cin >> s >> p;


                print_error();
                break;
            }
            case GET_LR:
            {
                cin >> s >> p;

                    print_error();

                        print_error();

                break;
            }
            case GET_LS:
            {
                cin >> p;

                if (p >= places_quantity || p < 0)
                    print_error();
                else
                {
                        print_error();
                }
                break;
            }
            case END:
            {
                run_loop = false;
                break;
            }
            default: {
                break;
            }
        }

    } while (run_loop);

}
