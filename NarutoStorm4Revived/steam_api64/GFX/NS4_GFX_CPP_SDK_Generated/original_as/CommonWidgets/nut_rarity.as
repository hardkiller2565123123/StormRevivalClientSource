package script.icon_rarity
{
   import flash.display.MovieClip;
   
   public class nut_rarity extends MovieClip
   {
      
      public function nut_rarity()
      {
         super();
      }
      
      public function SetRarity(param1:int) : *
      {
         switch(param1)
         {
            case 0:
               gotoAndStop("n");
               break;
            case 1:
               gotoAndStop("r");
               break;
            case 2:
               gotoAndStop("sr");
               break;
            case 3:
               gotoAndStop("ur");
               break;
            case 4:
               gotoAndStop("sc");
         }
      }
   }
}

