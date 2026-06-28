package script.icon_btl
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public class nut_icon_btl extends MovieClip
   {
      
      public function nut_icon_btl()
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

