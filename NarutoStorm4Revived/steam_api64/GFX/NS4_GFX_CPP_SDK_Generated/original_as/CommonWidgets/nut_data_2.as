package script.net_bingo
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import flash.net.URLRequest;
   import script.xcmn_font.smb_font;
   
   public class nut_data extends MovieClip
   {
      
      private var m_book:smb_book = null;
      
      private var m_title:smb_font = null;
      
      private var m_reward:smb_font = null;
      
      private var m_item:smb_font = null;
      
      private var m_itemNum:smb_font = null;
      
      private var m_dmyIcon:MovieClip = null;
      
      private var m_dmyName:MovieClip = null;
      
      private var m_iconLoader:ExtendLoader = null;
      
      private var m_nameLoader:ExtendLoader = null;
      
      private var m_isLoaded:Boolean = false;
      
      public function nut_data()
      {
         super();
         this.m_title = this["txt_title"];
         this.m_reward = this["txt_reward"];
         this.m_item = this["txt_item"];
         this.m_itemNum = this["txt_num"];
         this.m_dmyIcon = this["dmy_charicon_l"];
         this.m_dmyName = this["dmy_name_m"];
         this.m_book = this["mc_book"];
         this.m_title.SetText(String(ExternalInterface.call("MessageConvert","network_sys_202")));
         this.m_reward.SetText(String(ExternalInterface.call("MessageConvert","eventcheck_018")));
         this.m_title.visible = false;
         this.m_reward.visible = false;
         this.m_item.visible = false;
         this.m_itemNum.visible = false;
         this.m_dmyIcon.visible = false;
         this.m_dmyName.visible = false;
         addEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
         stop();
         visible = false;
      }
      
      public function RequestCreateBookAndPlayInAnm(param1:String, param2:String) : *
      {
         gotoAndStop("in");
         this.m_iconLoader = new ExtendLoader();
         var _loc3_:URLRequest = new URLRequest(param1);
         this.m_iconLoader.load(_loc3_);
         this.m_dmyIcon.addChild(this.m_iconLoader);
         this.m_iconLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         this.m_iconLoader.visible = false;
         this.m_nameLoader = new ExtendLoader();
         var _loc4_:URLRequest = new URLRequest(param2);
         this.m_nameLoader.load(_loc4_);
         this.m_dmyName.addChild(this.m_nameLoader);
         this.m_nameLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         addEventListener(Event.ENTER_FRAME,this.OnUpdate);
         this.m_nameLoader.visible = false;
         this.m_isLoaded = false;
      }
      
      public function SetRewardItemInfo(param1:String, param2:uint) : *
      {
         this.m_item.SetText(param1);
         this.m_itemNum.SetText(String(ExternalInterface.call("MessageConvert","eventcheck_023")));
         var _loc3_:Array = new Array();
         _loc3_.push(param2.toString());
         this.m_itemNum.ReplaceTextList(_loc3_);
      }
      
      public function RequestDeleteBook() : *
      {
         this.m_dmyIcon.removeChild(this.m_iconLoader);
         this.m_iconLoader.unload();
         this.m_iconLoader = null;
         this.m_dmyName.removeChild(this.m_nameLoader);
         this.m_nameLoader.unload();
         this.m_nameLoader = null;
         this.m_title.visible = false;
         this.m_reward.visible = false;
         this.m_item.visible = false;
         this.m_itemNum.visible = false;
         this.m_dmyIcon.visible = false;
         this.m_dmyName.visible = false;
         if(hasEventListener(Event.ENTER_FRAME))
         {
            removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
      }
      
      private function OnUpdate(param1:Event) : *
      {
         if(this.m_isLoaded == false)
         {
            if(this.m_iconLoader.IsLoadedXfbin() && this.m_nameLoader.IsLoadedXfbin())
            {
               visible = true;
               gotoAndPlay("in");
               this.m_isLoaded = true;
            }
         }
         else if(currentLabel == "loop")
         {
            this.m_title.visible = true;
            this.m_reward.visible = true;
            this.m_item.visible = true;
            this.m_itemNum.visible = true;
            this.m_dmyIcon.visible = true;
            this.m_dmyName.visible = true;
            if(this.m_nameLoader != null && this.m_iconLoader != null)
            {
               this.m_iconLoader.visible = true;
               this.m_nameLoader.visible = true;
            }
            removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
      }
      
      private function OnRemove(param1:Event) : *
      {
         if(hasEventListener(Event.ENTER_FRAME))
         {
            removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
         removeEventListener(Event.REMOVED_FROM_STAGE,this.OnRemove);
      }
   }
}

