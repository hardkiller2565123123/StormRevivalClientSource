package script.icon_rate_s
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public class nut_rate_s extends MovieClip
   {
      
      public function nut_rate_s()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

