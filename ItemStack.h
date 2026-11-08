#ifndef ITEMSTACK_H
#define ITEMSTACK_H
class Item;

class ItemStack{

    public:
        ItemStack(Item* item, int count);
        Item* getItem();
        int getItemCount();
        int takeItems(int n);
        void setItemCount(int count);
        void incCount(int n);
        void decCount(int n);

    private:
        int count;
        Item* item;


};


#endif