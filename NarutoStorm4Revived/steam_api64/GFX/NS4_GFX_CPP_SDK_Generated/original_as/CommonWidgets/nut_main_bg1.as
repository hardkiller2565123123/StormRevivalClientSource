package script.gauge_cmn
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol92")]
   public class nut_main_bg1 extends MovieClip
   {
      
      public function nut_main_bg1()
      {
         super();
         addFrameScript(0,this.frame1,49,this.frame50,82,this.frame83);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame50() : *
      {
         gotoAndPlay("awk1_loop");
      }
      
      internal function frame83() : *
      {
         gotoAndPlay("awk2_loop");
      }
   }
}

