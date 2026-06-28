package shop_catalog_fla
{
   import adobe.utils.*;
   import flash.accessibility.*;
   import flash.desktop.*;
   import flash.display.*;
   import flash.errors.*;
   import flash.events.*;
   import flash.external.*;
   import flash.filters.*;
   import flash.geom.*;
   import flash.globalization.*;
   import flash.media.*;
   import flash.net.*;
   import flash.net.drm.*;
   import flash.printing.*;
   import flash.profiler.*;
   import flash.sampler.*;
   import flash.sensors.*;
   import flash.system.*;
   import flash.text.*;
   import flash.text.engine.*;
   import flash.text.ime.*;
   import flash.ui.*;
   import flash.utils.*;
   import flash.xml.*;
   import script.icon_checkbox.nut_checkbox;
   import script.icon_new.nut_new;
   import script.icon_rarity.nut_rarity;
   import script.net_card.anm_card_skin;
   import script.shop_cmn.nut_blank;
   import script.shop_cmn.nut_sold;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_plate_skin_4 extends MovieClip
   {
      
      public var all_line:nut_line;
      
      public var mc_blank:nut_blank;
      
      public var mc_card_skin:anm_card_skin;
      
      public var mc_check:nut_checkbox;
      
      public var mc_new:nut_new;
      
      public var mc_rarity:nut_rarity;
      
      public var mc_skin_price:MovieClip;
      
      public var mc_sold:nut_sold;
      
      public var txt_skin_num:smb_font;
      
      public function anm_plate_skin_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4,4,this.frame5,5,this.frame6,6,this.frame7,7,this.frame8,8,this.frame9);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_skin_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_skin_num.SetTextSize(28);
         this.mc_skin_price.txt_skin_price.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.mc_skin_price.txt_skin_price.SetTextSize(30);
         this.txt_skin_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.mc_skin_price.txt_skin_price.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         this.txt_skin_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.mc_skin_price.txt_skin_price.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame3() : *
      {
         this.txt_skin_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.mc_skin_price.txt_skin_price.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame4() : *
      {
         this.txt_skin_num.SetTextColor(6970438);
         this.mc_skin_price.txt_skin_price.SetTextColor(6970438);
      }
      
      internal function frame5() : *
      {
         this.txt_skin_num.SetTextColor(6970438);
         this.mc_skin_price.txt_skin_price.SetTextColor(6970438);
      }
      
      internal function frame6() : *
      {
         this.txt_skin_num.SetTextColor(6970438);
         this.mc_skin_price.txt_skin_price.SetTextColor(6970438);
      }
      
      internal function frame7() : *
      {
         this.txt_skin_num.SetTextColor(6970438);
         this.mc_skin_price.txt_skin_price.SetTextColor(6970438);
      }
      
      internal function frame8() : *
      {
         this.txt_skin_num.SetTextColor(4920576);
         this.mc_skin_price.txt_skin_price.SetTextColor(4920576);
      }
      
      internal function frame9() : *
      {
         this.txt_skin_num.SetTextColor(4920576);
         this.mc_skin_price.txt_skin_price.SetTextColor(4920576);
      }
   }
}

