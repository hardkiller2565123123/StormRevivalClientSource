package script.icon_team
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_icon_team extends MovieClip
   {
      
      public function nut_icon_team()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
      
      internal function frame3() : *
      {
         this.stop();
      }
   }
}

