package script.cutin_trans
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_in extends MovieClip
   {
      
      public function nut_in()
      {
         super();
         addFrameScript(6,this.frame7);
      }
      
      internal function frame7() : *
      {
         stop();
      }
   }
}

