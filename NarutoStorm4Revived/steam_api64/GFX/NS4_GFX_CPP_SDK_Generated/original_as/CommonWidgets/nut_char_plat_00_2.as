package script.freebtl_course
{
   import ELoader.ExtendLoader;
   import flash.display.DisplayObject;
   import flash.display.DisplayObjectContainer;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import flash.net.URLRequest;
   
   public class nut_char_plat_00 extends MovieClip
   {
      
      public var GetCourseNum:Function;
      
      private var m_index:int;
      
      private var m_attachObj:MovieClip;
      
      private var m_loaderObj:ExtendLoader;
      
      private var m_url:URLRequest;
      
      private var m_charCode:String;
      
      private var m_isLoadCheck:Boolean;
      
      private var m_dmy:MovieClip = null;
      
      public function nut_char_plat_00()
      {
         super();
         this.m_index = 0;
         this.m_attachObj = null;
         this.m_loaderObj = null;
         this.m_url = null;
         this.m_charCode = "";
         this.m_isLoadCheck = false;
         this.m_dmy = this["dmy_char_face"];
      }
      
      public function Initialize(param1:int, param2:String) : void
      {
         if(param2 == null)
         {
            param2 = "";
         }
         this.m_index = param1;
         this.m_charCode = "sla_" + param2;
         this.RequestUnload();
         if(this.m_loaderObj == null && this.m_url == null)
         {
            this.m_loaderObj = new ExtendLoader();
            this.m_url = new URLRequest("../charicon_sla/" + this.m_charCode + ".xfbin");
            this.m_loaderObj.load(this.m_url);
            this.m_isLoadCheck = true;
            addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         }
         if(this.m_dmy != null)
         {
            this.m_dmy.visible = false;
         }
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         if(this.m_isLoadCheck)
         {
            if(this.m_loaderObj.IsLoadedXfbin())
            {
               this.onLoadComplete();
               this.m_isLoadCheck = false;
            }
         }
         if(this.m_attachObj != null)
         {
            this.m_attachObj.alpha = this.alpha;
         }
      }
      
      internal function onLoadComplete() : *
      {
         this.m_loaderObj.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         if(this.m_dmy != null)
         {
            this.m_dmy.visible = true;
            this.m_dmy.addChild(this.m_loaderObj);
            this.m_attachObj = this.m_dmy;
         }
         this.dbgShowChildren(this);
      }
      
      public function RequestUnload() : void
      {
         if(this.m_loaderObj != null)
         {
            if(this.m_attachObj)
            {
               this.m_attachObj.removeChild(this.m_loaderObj);
            }
            this.m_loaderObj.unload();
            this.m_loaderObj = null;
            this.m_url = null;
         }
      }
      
      public function dbgShowChildren(param1:*, param2:int = 0) : void
      {
         var _loc4_:DisplayObject = null;
         var _loc5_:String = null;
         var _loc6_:int = 0;
         if(param2 == 0)
         {
            if(param1 is DisplayObjectContainer)
            {
               trace("DisplayObjectContainer : " + param1.name,param1);
            }
            else
            {
               trace("DisplayObject : " + param1.name,param1);
            }
            param2 = 1;
         }
         var _loc3_:uint = 0;
         while(_loc3_ < param1.numChildren)
         {
            _loc4_ = param1.getChildAt(_loc3_);
            _loc5_ = "";
            _loc6_ = 0;
            while(_loc6_ < param2)
            {
               _loc5_ += " ";
               _loc6_++;
            }
            if(_loc4_ is DisplayObjectContainer)
            {
               trace(_loc5_ + "DisplayObjectContainer : " + _loc4_.name,_loc4_);
               this.dbgShowChildren(_loc4_,param2 + 1);
            }
            else
            {
               trace(_loc5_ + "DisplayObject : " + _loc4_.name,_loc4_);
            }
            _loc3_++;
         }
      }
   }
}

