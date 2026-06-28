package script.shop_cmn
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public class nut_top extends MovieClip
   {
      
      public var mc_deco:MovieClip;
      
      public var mc_topbar:MovieClip;
      
      public function nut_top()
      {
         super();
         addFrameScript(8,this.frame9,14,this.frame15);
      }
      
      internal function frame9() : *
      {
         stop();
      }
      
      internal function frame15() : *
      {
         stop();
      }
   }
}

