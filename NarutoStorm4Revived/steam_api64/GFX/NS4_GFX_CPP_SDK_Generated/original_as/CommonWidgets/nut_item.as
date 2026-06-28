package script.start_item
{
   import flash.display.MovieClip;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class nut_item extends MovieClip
   {
      
      public var mc_bar_00:anm_bar;
      
      public var mc_bar_01:anm_bar;
      
      public var mc_bar_02:anm_bar;
      
      public var mc_bar_03:anm_bar;
      
      public var mc_bar_04:anm_bar;
      
      public var mc_bar_05:anm_bar;
      
      public var mc_bar_06:anm_bar;
      
      public var mc_scb:nut_scb_bg;
      
      public var mc_title:smb_title;
      
      public function nut_item()
      {
         super();
         addFrameScript(6,this.frame7,11,this.frame12);
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame12() : *
      {
         stop();
      }
   }
}

