package script.gauge_cmn
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public class nut_break extends MovieClip
   {
      
      public function nut_break()
      {
         super();
         addFrameScript(22,this.frame23);
      }
      
      internal function frame23() : *
      {
         this.stop();
      }
   }
}

