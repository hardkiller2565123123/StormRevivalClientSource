package script.modesel_txt
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public class nut_mode_txt extends MovieClip
   {
      
      public function nut_mode_txt()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

