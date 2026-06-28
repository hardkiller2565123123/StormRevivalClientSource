package script.shop_preview
{
   import flash.display.MovieClip;
   import script.icon_collect_l.nut_name;
   import script.icon_kwrm_l.nut_kwrm_l;
   import script.xcmn_tex00.nut_tex00;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class nut_trade extends MovieClip
   {
      
      public var all_win:MovieClip;
      
      public var dmy_ougi:nut_tex00;
      
      public var dmy_ougifin:nut_tex00;
      
      public var mc_head:MovieClip;
      
      public var mc_kwrm:nut_kwrm_l;
      
      public var mc_list:smb_list2;
      
      public var mc_name:nut_name;
      
      public var mc_scb:nut_scb_bg;
      
      public var mc_total:smb_total;
      
      public function nut_trade()
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

