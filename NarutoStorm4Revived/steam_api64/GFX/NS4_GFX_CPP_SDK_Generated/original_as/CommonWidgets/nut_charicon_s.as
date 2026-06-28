package script.charicon_s
{
   import flash.display.MovieClip;
   
   public class nut_charicon_s extends MovieClip
   {
      
      public function nut_charicon_s()
      {
         super();
      }
      
      public function SetCharaCode(param1:String) : *
      {
         gotoAndStop(param1);
      }
   }
}

