package script.num_l
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol21")]
   public class nut_num_l extends MovieClip
   {
      
      public function nut_num_l()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function Set(param1:int) : void
      {
         var _loc2_:String = "num_" + param1 as String;
         gotoAndStop(_loc2_);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

