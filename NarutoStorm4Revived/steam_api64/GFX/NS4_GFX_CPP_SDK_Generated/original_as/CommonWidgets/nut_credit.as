package script.freebtl_tonmt
{
   import flash.display.MovieClip;
   import script.xcmn_unset.nut_credit00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class nut_credit extends MovieClip
   {
      
      public var mc_credit:nut_credit00;
      
      public function nut_credit()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
      }
      
      internal function frame6() : *
      {
         stop();
      }
      
      internal function frame11() : *
      {
         stop();
      }
   }
}

