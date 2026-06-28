package script.icon_checkbox
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_checkbox extends MovieClip
   {
      
      public function nut_checkbox()
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

