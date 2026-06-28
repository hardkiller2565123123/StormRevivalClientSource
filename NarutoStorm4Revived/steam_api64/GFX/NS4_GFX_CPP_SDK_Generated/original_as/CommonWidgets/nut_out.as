package script.cutin_trans
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class nut_out extends MovieClip
   {
      
      public function nut_out()
      {
         super();
         addFrameScript(7,this.frame8);
      }
      
      internal function frame8() : *
      {
         stop();
      }
   }
}

