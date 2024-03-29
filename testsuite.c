
#include "kprintf.h"

const char* decl =
"\fIN CONGRESS, July 4, 1776.\n\n"
"The unanimous Declaration of the thirteen united States of America,\n\n"
"When in the Course of human events, it becomes necessary for one people to "
"dissolve the political bands which have connected them with another, "
"and to assume among the powers of the earth, the separate and equal station to "
"to which the Laws of Nature and of Nature's God entitle them, a decent "
"respect to the opinions of mankind requires that they should declare the "
"causes which impel them to the separation. \n\n"
"We hold these truths to be self-evident, that all men are created equal, "
"that they are endowed by their Creator with certain unalienable Rights, that "
"among these are Life, Liberty and the pursuit of Happiness. \n"
"\t--That to secure these rights, Governments are instituted among Men,\n"
" \t--That whenever any Form of Government becomes destructive of these "
"ends, it is the Right of the\t\tPeople\t\tto alter or to abolish it, and to "
"institute new Government, laying its foundation on such principles and "
"organizing its powers in such form, as to them shall seem most likely to "
"effect their Safety and Happiness.\n"
"\n"
"Prudence, indeed, will dictate that Governments long established should not "
"be changed for light and transient causes;and accordingly all experience hath"
"shewn, that mankind are more disposed to suffer, while evils are sufferable, "
"than to right themselves by abolishing the forms to which they are "
"accustomed. But when a long train of abuses and usurpations, pursuing "
"invariably the same Object evinces a design to reduce them under absolute Despotism, "
"it is their right, it is their duty, to throw off such Government,  "
"and to provide new Guards for their future security.\n"
"   \t--Such has been the patient sufferance of these Colonies; and such is now the "
"necessity which constrains them to alter their former Systems of Government. "
"The history of the present King of Great Britain is a history of repeated injuries "
"and usurpations, all having in direct object the establishment of an absolute Tyranny "
"over these States. To prove this, let Facts be submitted to a candid world.\n"
"...";
const char* decl2 =
"In every stage of these Oppressions We have Petitioned for Redress in the most "
"humble terms: Our repeated Petitions have been answered only by repeated injury. "
"A Prince whose character is thus marked by every act which may define a Tyrant, "
"is unfit to be the ruler of a free people.\n"
"Nor have We been wanting in attentions to our Brittish brethren. We have warned them "
"from time to time of attempts by their legislature to extend an unwarrantable jurisdiction "
"over us. We have reminded them of the circumstances of our emigration and settlement "
"here. We have appealed to their native justice and magnanimity, and we have conjured "
"them by the ties of our common kindred to disavow these usurpations, which, would "
"inevitably interrupt our connections and correspondence. They too have been deaf "
"to the voice of justice and of consanguinity. \nWe must, therefore, acquiesce in the "
"necessity, which denounces our Separation, and hold them, as we hold the rest of mankind, "
"Enemies in War, in Peace Friends.\n"
"We, therefore, the Representatives of the united States of "
"America, in General Congress, "
"Assembled, appealing to the Supreme Judge of the world for the rectitude of our intentions, "
"do, in the Name, and by Authority of the good People of these Colonies, solemnly "
"publish and declare, That these \tUnited Colonies \t\tare, and of Right ought to be Free and "
"Independent States; that they are Absolved from all Allegiance to the British Crown, "
"and that all political connection between them and the State of Great Britain, "
"is and ought to be totally dissolved; and that as Free and Independent States, "
"they have full Power to levy War, conclude Peace, contract Alliances, establish Commerce, "
"and to do all other Acts and Things which Independent States may of right do. "
"And for the support of this Declaration, with a firm reliance on the protection of "
"divine Providence, we mutually pledge to each other our Lives, our Fortunes and our sacred Honor.\n"
"fooby dooby doo...";

const char* phrase = "Saruman the Many-Colored "
                    "Saruman the Many-Colored "
                    "Saruman the Many-Colored";

void sweet(){
    kprintf("%s",decl);
    int i;
    int mode=0;
    int fg=7,bg=2;
    for(i=0;phrase[i];++i){
        kprintf("%c", phrase[i]);
        if( phrase[i] == ' '){
            mode = 1-mode;
            fg=7;
            bg=1;
        }
        if( mode == 0 )
            fg = (fg+i)&15;
        else
            bg = (bg-i)&15;
    }
    kprintf("\n%s",decl2);
    kprintf("\r%d %d %d %d %d%c%d...",42,43,44,45,46,127,47);
}
