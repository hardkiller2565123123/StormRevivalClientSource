package script.icon_vs_l
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_vs_l extends MovieClip
   {
      
      public function nut_vs_l()
      {
         super();
         addFrameScript(234,this.frame235);
      }
      
      internal function frame235() : *
      {
         gotoAndPlay("loop");
      }
   }
}

