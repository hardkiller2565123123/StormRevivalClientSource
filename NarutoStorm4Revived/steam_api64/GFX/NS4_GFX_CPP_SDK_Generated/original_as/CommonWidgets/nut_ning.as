package script.start_ning
{
   import flash.display.MovieClip;
   import script.shop_cmn.nut_help;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol23")]
   public dynamic class nut_ning extends MovieClip
   {
      
      public var mc_bar_00:anm_bar;
      
      public var mc_bar_01:anm_bar;
      
      public var mc_bar_02:anm_bar;
      
      public var mc_bar_03:anm_bar;
      
      public var mc_bar_04:anm_bar;
      
      public var mc_bar_05:anm_bar;
      
      public var mc_bar_06:anm_bar;
      
      public var mc_help:nut_help;
      
      public var mc_palette_all:MovieClip;
      
      public var mc_scb:nut_scb_bg;
      
      public var mc_txt_item:MovieClip;
      
      public var mc_txt_own:MovieClip;
      
      public var mc_win_base:MovieClip;
      
      public function nut_ning()
      {
         super();
         addFrameScript(6,this.frame7,12,this.frame13);
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame13() : *
      {
         stop();
      }
   }
}

