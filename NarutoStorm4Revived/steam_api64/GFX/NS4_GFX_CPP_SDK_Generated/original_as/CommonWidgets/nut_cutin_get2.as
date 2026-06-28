package script.icon_item2
{
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public dynamic class nut_cutin_get2 extends MovieClip
   {
      
      public var dmy_icon_mtr:nut_tex00;
      
      public var mc_bg:MovieClip;
      
      public var mc_eff:MovieClip;
      
      public var mc_item_txt:MovieClip;
      
      public function nut_cutin_get2()
      {
         super();
         addFrameScript(0,this.frame1,5,this.frame6,9,this.frame10,14,this.frame15);
      }
      
      internal function frame1() : *
      {
         this.mc_eff.stop();
      }
      
      internal function frame6() : *
      {
         this.mc_eff.play();
      }
      
      internal function frame10() : *
      {
         stop();
      }
      
      internal function frame15() : *
      {
         stop();
      }
   }
}

